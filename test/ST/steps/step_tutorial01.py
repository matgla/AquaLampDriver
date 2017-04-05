# file:features/steps/step_tutorial01.py
# ----------------------------------------------------------------------------
# STEPS:
# ----------------------------------------------------------------------------
from behave import given, when, then
import time
from framework.test_utils import TestFramework
from messages import messages
import binascii
from logging import getLogger

logger = getLogger("TEST")


@given('we have behave installed')
def step_impl(context):
    tf = TestFramework()
    tf.init_framework()

    connection = tf.get_connection()

    time.sleep(0.2)

    #msg = messages.ClientInfo(8, "abcd\0")

    msg = bytearray()
    msg.append(7)
    msg.append(8)
    msg.append(0x0b)
    msg.append('T')
    msg.append('E')
    msg.append('S')
    msg.append('T')
    msg.append(0)

    logger.debug("ClientInfo: " + binascii.hexlify(msg))
    connection.write(msg)

    time.sleep(0.2)

    tf.teardown()
    pass


@when('we implement a test')
def step_impl(context):
    assert True is not False


@then('behave will test it for us!')
def step_impl(context):
    assert context.failed is False
