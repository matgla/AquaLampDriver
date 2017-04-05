class BuilderFactory:


    def generate_target(self):
        raise NotImplementedError("Please implement this abstract method")
    
    def generate_tests(self):
        raise NotImplementedError("Please implement this abstract method")

    def build_target(self):
        raise NotImplementedError("Please implement this abstract method")
        
    def build_unit_tests(self):
        raise NotImplementedError("Please implement this abstract method")
        
    def run_system_tests(self):
        raise NotImplementedError("Please implement this abstract method")