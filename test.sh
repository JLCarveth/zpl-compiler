# Tests the Scanner against a set of input files
COMPILER=out/ZiroCompiler
INPUT_DIR=input/
OUTPUT_DIR=out/
NUM_TESTS=$(ls $INPUT_DIR | wc -l)
SUCCESSFUL_TESTS=0

printf "====================================================================================\n"
printf "* %-80s *\n" " _____   ___  __     ___                      _ _           "
printf "* %-80s *\n" "/ _  /  / _ \/ /    / __\___  _ __ ___  _ __ (_) | ___ _ __ "
printf "* %-80s *\n" "\// /  / /_)/ /    / /  / _ \| '_ \` _ \| '_ \| | |/ _ \ '__|"
printf "* %-80s *\n" " / //\/ ___/ /___ / /__| (_) | | | | | | |_) | | |  __/ |   "
printf "* %-80s *\n" "/____/\/   \____/ \____/\___/|_| |_| |_| .__/|_|_|\___|_|   "
printf "* %-80s *\n" "                                       |_|                  "
printf "====================================================================================\n"
printf "* %-80s *\n" "Made by John L. Carveth, 2021"
printf "* %-80s *\n" "Version 0.1.0"
printf "====================================================================================\n"

printf "* %-80s *\n" "Beginning Zero Compiler tests ($NUM_TESTS)..."
# For each of the input test files, 
for file in $(ls input/)
do
    printf "* %-80s *\n" "Testing $file"
    $COMPILER 1 $INPUT_DIR$file 1> $OUTPUT_DIR$file.out 2> $OUTPUT_DIR$file.err
    if [ ! -s $OUTPUT_DIR$file.err ]
    then
        SUCCESSFUL_TESTS=$((SUCCESSFUL_TESTS+1))
    else
        printf "* %-80s *\n" "Testing $file has failed. See $OUTPUT_DIR$file.err for more information."
    fi
done
printf "* %-80s *\n" "Completed $NUM_TESTS Tests."
printf "* %-80s *\n" "$SUCCESSFUL_TESTS/2 Tests passed."
printf "====================================================================================\n"