#!/usr/bin/python

from os import path
from subprocess import call
from colorama import init, Fore, Back, Style
from build_system.runner import Runner
import argparse
import re
import sys

init()  # init colorama


def main():
    default_target = "stm32f429-Discovery"

    parser = argparse.ArgumentParser()
    parser.add_argument('-n', '--native-builder', dest='native', action='store_true',
                        help='don\'t use Docker')
    parser.add_argument('-b', '--build', dest='build', action='store_true',
                        help='build project')
    parser.add_argument('-t', '--target', dest='target', nargs='?', type=str, default=default_target,
                        help='select target, default=' + default_target)
    parser.add_argument('-g', '--generate', dest='generate', action='store_true',
                        help='generate project')
    parser.add_argument('-a', '--test', dest='all_tests', action='store_true',
                        help='run all tests')
    parser.add_argument('-c', '--generate_test', dest='generate_test', action='store_true',
                        help='generate sources for unit tests')
    parser.add_argument('-r', '--rebuild', dest='rebuild', action='store_true',
                        help='rebuild project (generate & build)')
    parser.add_argument('-u', '--ut', dest='ut', action='store_true',
                        help='run unit tests')
    parser.add_argument('-s', '--st', dest='st', action='store_true',
                        help='run system tests')
    parser.add_argument('-f', '--force', dest='force', action='store_true',
                        help='building even if the step failed')
    parser.add_argument('-l', '--lsan', dest='lsan', action='store_true',
                        help='leak sanitizer')
    parser.add_argument('-e', '--asan', dest='asan', action='store_true',
                        help='address sanitizer')

    args = parser.parse_args()

    runner = Runner(args)

    print Fore.BLUE + '===================================\n' \
                    + '=  STM32 BootLoader Build System  =\n' \
                    + '===================================' + Style.RESET_ALL

    runner.print_commands_to_be_executed()
    rc = runner.execute_commands()
    print "Return code is " + str(rc)
    sys.exit(rc)

if __name__ == "__main__":
    main()
