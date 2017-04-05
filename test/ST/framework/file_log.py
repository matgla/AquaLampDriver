import logging


def setup_logger(name, log_to_file, log_level, log_file):
    form = '%(asctime)s %(module)s::%(levelname)s: %(message)s'
    formatter = logging.Formatter(form)

    if log_to_file:
        with open(log_file, 'w'):
            pass
        fh = logging.FileHandler(log_file)
        fh.setLevel(log_level)
        fh.setFormatter(formatter)
        logger = logging.getLogger(name)
        logger.setLevel(log_level)
        logger.addHandler(fh)
