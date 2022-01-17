import os
import pandas as pd
import pysam
from pysam import VariantFile
import argparse

def paf2vcf(pafPath:"str",vcfPath: "str", maxIndelSize:"int"=10000 ):
    '''
    Use this on variant call files from PAF files (Mapping of a whole genome sample to its reference)
    using paftools.js from Minimap2
    '''
    sampleName = pafPath[::-1][:pafPath[::-1].find("/")][::-1] if "/" in pafPath else pafPath # NOT ESSENTIAL, just cleans up sample name if input is from another dir
    sampleName = sampleName[:sampleName.index(".var")]
    # outputName = vcfPath + sampleName + ".vcf" if "/" in vcfPath else vcfPath + "/" + sampleName + ".vcf"
    outputName = vcfPath
    with open(outputName, "w") as myvcf:
        myvcf.write("##fileformat=VCFv4.2\n") # hardcoded
        myvcf.write("##contig=<ID=NC_007795.1,length=2821361>\n") # hardcoded, length is taken from the {index .fai file} associated with {reference file}
        myvcf.write('##FORMAT=<ID=GT,Number=1,Type=String,Description="Genotype">)\n') # hardcoded
    # NEED TO EXCLUDE ROWS WITH R IN PAF[0]
    pafDF = pd.read_csv(pafPath, skiprows=1, sep="\t", names=["STAT", "CHROM", "START", "STOP", "DP", "QUAL", "REF", "ALT", "ASM", "QS", "QE", "STRAND"])
    pafDF = pafDF[pafDF["STAT"].str.contains("R")==False] # Removes all R-typed lines in .paf (Feature seems specific to Minimap2)
    # Following 2 mods may be unneccessary, redo samples! Make sure to use SAME REF with DIFF SAMPLES, might try bcftools norm 
    pafDF = pafDF[pafDF["REF"].str.len() < maxIndelSize] # Removes all rows with REF indel > maxIndelSize
    pafDF = pafDF[pafDF["ALT"].str.len() < maxIndelSize] # Removes all rows with REF indel > maxIndelSize
    rowNum = pafDF.shape[0]
    CHROM = pafDF.iloc[:,1].tolist()
    POS = pafDF.iloc[:,3].tolist()
    ID = ["."]*rowNum 
    REF = pafDF.iloc[:,6].tolist()
    ALT = pafDF.iloc[:,7].tolist()
    QUAL = pafDF.iloc[:,5].tolist()
    FILTER = ["."]*rowNum 
    INFO = ["."]*rowNum 
    FORMAT = ["GT"]*rowNum # Only FORMAT feature I have down right now is genotype. It seems like the only one I have info on from the paftools variant call
    SAMPLE = ["1"]*rowNum # Since Staph is a bacteria with only one CHROM, it only has 1 haplotype
    dfVCF = pd.DataFrame(list(zip(CHROM, POS, ID, REF, ALT, QUAL, FILTER, INFO, FORMAT, SAMPLE)), columns =["#CHROM", "POS", "ID", "REF", "ALT", "QUAL", "FILTER", "INFO", "FORMAT", sampleName])
    dfVCF = dfVCF.sort_values(by=["POS"]) # Sorts rows vcf dataframe by position column
    dfVCF.to_csv(outputName, sep="\t", index = False, mode="a") # Convert vcf dataframe to vcf file
    return

def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-i","--indir", help="Enter file path containing variant call files called from .paf files with / at end of path")
    parser.add_argument("-o","--outdir", help="Enter file path to place variant call files called as .vcf files with / at end of path")
    args = parser.parse_args()

    pafPath = args.indir
    vcfPath = args.outdir
    paf2vcf(pafPath=pafPath, vcfPath=vcfPath)

if __name__ == "__main__":
    main()

8