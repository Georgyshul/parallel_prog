#!/usr/bin/python3

import pandas as pd
import glob

csv_files = glob.glob('log/stat_avg_*.csv')
csv_files.sort()

combined_data = pd.DataFrame(range(1, 11))


for i, file in enumerate(csv_files):
    df = pd.read_csv(file, header=None)
    combined_data = combined_data.merge(df, on=0, how='left')
    combined_data = combined_data.rename(columns={1: "Type %d"%i})

combined_data = combined_data.rename(columns={0: "Thds num."})

combined_data.to_csv('./log/average_times.csv', index=False)