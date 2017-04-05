from os import path

from builder import Builder


def get_common_command():
    return " -c \"source ~/.bashrc && cd /mnt/source/scripts && "


class DockerDefaultBuilder(Builder):

    def getDockerCommand(self):
        return "run"

    def getImageName(self):
        return " matgla/docker_stm"

    def getMountCommand(self):
        path_to_working_dir = path.dirname(
            path.abspath(__file__))

        if path_to_working_dir.find(":") != -1:
            path_to_working_dir = "//" + path_to_working_dir
            path_to_working_dir = path_to_working_dir.replace("\\", "//")
            path_to_working_dir = path_to_working_dir.replace(":", "")
            path_to_working_dir = path_to_working_dir[
                :path_to_working_dir.rfind("/") - 1]
            path_to_working_dir = path_to_working_dir[
                :path_to_working_dir.rfind("/") - 1]
        return " -v " + path_to_working_dir + ":/mnt/source"

    def getLoginCmd(self):
        return " su - admin -s /bin/bash"

    def getShellCmd(self):
        return " -c \"\""

    def getColors(self):
        return " -it --privileged=true -e \"TERM=xterm-256color\""

    def get_cmd(self):
        return "docker " + self.getDockerCommand() + self.getColors() + \
            self.getMountCommand() + self.getImageName() + \
            self.getLoginCmd() + self.getShellCmd()


class DockerGenerateBuilder(DockerDefaultBuilder):

    def get_cmd_name(self):
        return "generate target"

    def getShellCmd(self):
        return get_common_command() + "sh generate.sh\""


class DockerTargetBuilder(DockerDefaultBuilder):

    def get_cmd_name(self):
        return "build target"

    def getShellCmd(self):
        return get_common_command() + "sh build.sh\""


class DockerGenerateTestsBuilder(DockerDefaultBuilder):

    def get_cmd_name(self):
        return "generate tests"

    def getShellCmd(self):
        return get_common_command() + "sh generate_tests.sh -DLSAN=ON -DASAN=ON\""


class DockerUnitTestBuilder(DockerDefaultBuilder):

    def get_cmd_name(self):
        return "build & run UTs"

    def getShellCmd(self):
        return get_common_command() + "sh test_ut.sh -g\""


class DockerSystemTestRunner(DockerDefaultBuilder):

    def get_cmd_name(self):
        return "run STs"

    def getShellCmd(self):
        return get_common_command() + " sudo /usr/bin/startup.sh && sudo stty -ocrnl && sh test_st.sh\""
