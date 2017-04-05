from os import path
from builder_factory import BuilderFactory
import docker_builders

class DockerBuilderFactory(BuilderFactory):
    def build_target(self):
        return docker_builders.DockerTargetBuilder()

    def build_unit_tests(self):
        return docker_builders.DockerUnitTestBuilder()

    def generate_target(self):
        return docker_builders.DockerGenerateBuilder()

    def generate_tests(self):
        return docker_builders.DockerGenerateTestsBuilder()

    def run_system_tests(self):
        return docker_builders.DockerSystemTestRunner()
