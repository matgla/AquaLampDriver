class Builder:

    def get_cmd_name(self):
        raise NotImplementedError("Please implement this abstract method")

    def get_cmd(self):
        raise NotImplementedError("Please implement this abstract method")