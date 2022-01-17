#Notes:

### Restriction Enzymes
- An enzyme with a partner (usually a methylase)
- Recognize a sequence in DNA and makes a cut (double stranded cut)
    - Cut is a single peptide, but a dimer
    - Cut site ends up being a reverse complement palindrome
    - ACTG is a recognition site
    - There could be a cut after the A and after the T
        - We would then have a cut called a sticky end
- Methylase recognizes the same size and instead of cutting, it methylates the base
    - After methylation, the cutter won't cut
- Purpose: Target a piece of viral DNA which is present in a cell
    - If a piece is not methylated, cutter cuts DNA
    - Part of the immune system of a bacterial or archaeal cell
- NEBL made monay off dis

### What can we do about Plasmids not Working?
- We are trying to do genetics in a cyanobacterium, Spiroulina
    - We want Spiroulina to taste like mango and cinnamon
    - Spiroulina keeps cutting our shit tho, therefore we can't get DNA for flavors into genome
- We sequence the genome for Spiroulina
- We should methylate the genes in Spiroulina
    - If Spiroulina has a gene that cuts DNA, does it have that DNA?
- Given a genome, how would we find a sequence that isn't there???
    - Do we have a way of predicting how many of a given sequence should be present in our genome?
        - Make a NULL model lol
        - Compare how many sequences should be there and how many sequences are there
        - Get surprise factor from NULL model
        - We want to exclude these missing sequences
- We could potentially eliminate the sites which keep getting cut in our plasmid and fly under the radar of our organism.

### What we will do in our Next Assignemnt:
- We look for subsequences in a genome which could be of the size to be cut by RE's
- We look for the cases which appear to be under represented
    - This is an exercise in a NULL model
    - Consider a profile matrix
- Most common sizes for RE recognition sites are 4s, 5s, and 6s
- If we were given a sequence ACGT, how would we find how many that we'd expect in the genome
- We could go through all nucs in a genome and make rel freqs out of all them
    - Assuming nucs were randomly placed, we'd just multiply the seq's respective probabilities
    - Then we compare the expected value (after finding probabilities) with our observed values
- Instead we make use of the binomial equation to calculate mean and variance
- With this distribution, we can decide whether we are happy or sad
- Our assumption that these nucs are independent is kinda bad tho
- Codon formations cause bias
    - Most common amino acid is Alanine (~10% of all amino acids in genomes!)
    - Most rare amino acid is Tryptophan (~1%)
    - Clear bias towards some aminos and thus some nucs
- Let's make a more informed null model
    - Instead of nucleotides, let's use dinucleotides or trinucleotides
    - These are described by Markov Chains or Markov Models
    - Markov(0) represents single nucleotides
    - Markov(1) considers 4 diff probs of A based on the nucleotides that precede it
        - Looks at al 4 dinucleotides that end in A
