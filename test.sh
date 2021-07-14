COMPILER=out/ZiroCompiler

print_logo () {
    printf "*********************************************************************\n"
    printf "*  ___________  _         _____                      _ _            *\n"
    printf "* |___  /  __ \| |       / ____|                    (_) |           *\n"
    printf "*    / /| |__) | |      | |     ___  _ __ ___  _ __  _| | ___ _ __  *\n"
    printf "*   / / |  ___/| |      | |    / _ \| '_ \` _ \| '_ \| | |/ _ \ '__| *\n"
    printf "*  / /__| |    | |____  | |___| (_) | | | | | | |_) | | |  __/ |    *\n"
    printf "* /_____|_|    |______|  \_____\___/|_| |_| |_| .__/|_|_|\___|_|    *\n"
    printf "*                                             | |                   *\n"
    printf "*                                             |_|                   *\n"
    printf "*********************************************************************\n"
}
print_logo
printf 'Beginning Zero Compiler tests...\n'
$COMPILER 1 input/hello_world.z 1> out/hello_world.z.out 2> out/hello_world.z.err
$COMPILER 1 input/large.z 1> out/large.z.out 2> out/large.z.err
# TODO Examine contents of error files, if empty then test has passed.
printf 'Completed 2/2 Tests.\n'
printf 'Passed ?/2 Tests.\n'