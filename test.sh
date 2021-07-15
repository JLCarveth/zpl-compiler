COMPILER=out/ZiroCompiler

print_logo () {
    printf "=====================================================\n"
    printf "*   _______ _       ___                _ _          *\n"
    printf "*  |_  / _ \ |     / __|___ _ __  _ __(_) |___ _ _  *\n"
    printf "*   / /|  _/ |__  | (__/ _ \ '  \| '_ \ | / -_) '_| *\n"
    printf "*  /___|_| |____|  \___\___/_|_|_| .__/_|_\___|_|   *\n"
    printf "*                                |_|                *\n"
    printf "=====================================================\n"
}
print_logo
printf 'Beginning Zero Compiler tests...\n'
$COMPILER 1 input/hello_world.z 1> out/hello_world.z.out 2> out/hello_world.z.err
$COMPILER 1 input/large.z 1> out/large.z.out 2> out/large.z.err
# TODO Examine contents of error files, if empty then test has passed.
printf 'Completed 2/2 Tests.\n'
printf 'Passed ?/2 Tests.\n'