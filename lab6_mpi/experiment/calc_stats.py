#!/usr/bin/python3

import pandas as pd
import glob

csv_files = glob.glob('log/stat_avg_*.csv')
csv_files.sort()

for i, file in enumerate(csv_files):
    df = pd.read_csv(file, header=None)

    linear_time = df[1].loc[0]
    df[2] = linear_time / df[1]
    df[3] = df[2] / df[0]

    speedup = df[[0, 2]]
    efficiency = df[[0, 3]]
    
    speedup.to_csv(file.replace('avg', 'speedup'), index=False, header=False)
    efficiency.to_csv(file.replace('avg', 'efficiency'), index=False, header=False)
