from subprocess import call
from colorama import init, Fore, Back, Style
from build_system.builders.docker_builder_factory import DockerBuilderFactory
from build_system.builders.native_builder_factory import NativeBuilderFactory


class Runner:

    def __init__(self, args):
        self.args = args
        self.__parse_args()

    def print_commands_to_be_executed(self):
        for command in self.commands_to_run:
            print Fore.GREEN + 'Selected command: ' + Fore.YELLOW + \
                command.get_cmd_name() + Style.RESET_ALL

    def __get_max_command_name_len(self):
        max_length = 0
        for command in self.commands_to_run:
            if len(command.get_cmd_name()) > max_length:
                max_length = len(command.get_cmd_name())
        return max_length

    def __generate_spaces(self, start, end):
        return " " * (end - start + 1)

    def execute_commands(self):
        returncode = 0
        max_name_len = self.__get_max_command_name_len()
        for command in self.commands_to_run:
            print Fore.CYAN + '\nCalling: ' + Style.RESET_ALL + command.get_cmd()
            rc = call(command.get_cmd(), shell=True)
            step = 1
            if rc != 0:
                returncode = rc
            if not self.args.force and rc != 0:
                for passed_command in self.commands_to_run:
                    if passed_command != command:
                        print "STEP " + str(step) + ": " + passed_command.get_cmd_name() + self.__generate_spaces(len(passed_command.get_cmd_name()), max_name_len) + Fore.GREEN + " PASSED!" + Style.RESET_ALL
                        step = step + 1
                    else:
                        break
                print "STEP " + str(step) + ": " + command.get_cmd_name() + self.__generate_spaces(len(command.get_cmd_name()), max_name_len) + Fore.RED + " FAILED(" + str(rc) + ")!" + Style.RESET_ALL
                step = step + 1

                for stopped_command in self.commands_to_run[step - 1:]:
                    print "STEP " + str(step) + ": " + stopped_command.get_cmd_name() + self.__generate_spaces(len(stopped_command.get_cmd_name()), max_name_len) + Fore.YELLOW + " WASN'T RUN!" + Style.RESET_ALL
                    step = step + 1

                return returncode
        return returncode

    def __parse_args(self):
        self.commands_to_run = []
        if self.args.native:
            self.builder = NativeBuilderFactory()
        else:
            self.builder = DockerBuilderFactory()

        if self.args.generate or (self.args.rebuild and self.args.build):
            self.commands_to_run.append(self.builder.generate_target())
        if self.args.build or (self.args.rebuild and self.args.generate):
            self.commands_to_run.append(self.builder.build_target())
        if self.args.generate_test or (self.args.rebuild and self.args.ut) \
                or (self.args.all_tests and self.args.rebuild):
            self.commands_to_run.append(self.builder.generate_tests())
        if self.args.ut or (self.args.rebuild and self.args.generate_test) or self.args.all_tests:
            self.commands_to_run.append(self.builder.build_unit_tests())
        if self.args.st or self.args.all_tests:
            self.commands_to_run.append(self.builder.run_system_tests())
        if self.args.flash:
            self.commands_to_run.append(self.builder.flash_target())
