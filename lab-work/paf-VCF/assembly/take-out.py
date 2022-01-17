# use this to take out .fna files from NCBI data sets and bring them up to {assembly_data}
# place in ncbi dataset folder RIGHT after unzipping it
# brings .fna files 
import os
import sys
import argparse 
from timeit import timeit
# import multiprocessing as mp


def main():
    # print(mp.cpu_count())
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--path")
    args = parser.parse_args()
    
    path = args.path
    print(f"path is: {path}")
    for d in os.listdir(f"{path}/data/"):
        if "json" not in d:
            print(d) 
            os.system(f'mv {path}/data/{d}/*.fna {path}/.')

if __name__ == "__main__":

    main()
