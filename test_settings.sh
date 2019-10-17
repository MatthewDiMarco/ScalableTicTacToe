#!/bin/bash

# This script acts as a test harness for the TicTacToe C game, testing that
# all runs expectedly on startup given a valid or invalid settings file.

# Temp files and exit message
tempSet='temp_settings_file';
tempOut='temp_output_file';
tempExp='temp_expected_file';
Exit="failed to read temp_settings_file: shutting down...\n";
invalidRange="value must be between 3 and 999"; 

# Test index:
# 0: Invalid m/n range (low)
# 1: Invalid m/n range (high)
# 2: Invalid k range (low)
# 3: Invalid k range (high)
# 4: Negative values
# 5: Not a number
# 6: Bad format (missing setting/s)
# 7: Bad format (duplicate setting/s)
# 8: Bad format (Extra line)
# 9: Empty file

# Data
#------------------------------------------------------------------------------
declare -a testData=("M=3\nN=2\nK=3"        
                     "M=1000\nN=3\nK=3"
                     "M=3\nN=3\nK=2"
                     "M=3\nN=3\nK=1000"
                     "K=-3\nM=3\nN=3"
                     "N=three\nM=3\nK=3"
                     "M=3\nK=3"
                     "M=3\nM=3\nN=3\nK=3"
                     "M=3\nN=3\n\nK=3"
                     "");

declare -a expected=("$invalidRange at line 2\n$Exit" 
                     "$invalidRange at line 1\n$Exit"
                     "$invalidRange at line 3\n$Exit"
                     "$invalidRange at line 3\nK must be less than or equal to M, N or both\n$Exit"
                     "$invalidRange at line 1\n$Exit"
                     "$invalidRange at line 1\nline 2 has invalid format\n$Exit"
                     "missing setting 'N'\n$Exit"
                     "duplicate setting at line 2\n$Exit"
                     "line 3 has invalid format\n$Exit"
                     "line 1 has invalid format\nmissing setting 'M'\nmissing setting 'N'\nmissing setting 'K'\n$Exit");
#------------------------------------------------------------------------------

# Execute tests
i=0;
for element in "${testData[@]}"
do
    # Load up temp files
    echo -e "${testData[$i]}" > $tempSet;
    echo -e "${expected[$i]}" > $tempExp;
    
    # Execute and store actual out
    ./TicTacToe $tempSet > $tempOut;

    # Compare
    if diff $tempExp $tempOut > /dev/null; then
        echo test $i PASS;
    else
        echo test $i FAIL;
        echo expected...\[$(grep -E \? $tempExp)];
        echo but was....\[$(grep -E \? $tempOut)];
    fi
    i=$((i+1));
done

# Remove temporary files
rm $tempSet $tempOut $tempExp;
