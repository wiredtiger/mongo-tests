#!/usr/bin/env python
from unittest import TestCase

from bson import BSONCoding, dumps, loads, import_class


class TestData(BSONCoding):
    def __init__(self, *args):
        self.args = list(args)
        self.nested = None

    def bson_encode(self):
        return {"args": self.args, "nested": self.nested}

    def bson_init(self, raw_values):
        self.args = raw_values["args"]
        self.nested = raw_values["nested"]

    def __eq__(self, other):
        if not isinstance(other, TestData):
            return NotImplemented
        if self.args != other.args:
            return False
        if self.nested != other.nested:
            return False
        return True

    def __ne__(self, other):
        return not self.__eq__(other)


class TestObjectCoding(TestCase):
    def test_codec(self):
        import_class(TestData)
        data = TestData(u"Lorem ipsum dolor sit amet",
                        "consectetur adipisicing elit",
                        42)

        data2 = TestData(u"She's got both hands in her pockets",
                         "and she won't look at you won't look at you eh",
                         66,
                         23.54,
                         None,
                         True,
                         False,
                         u"Alejandro")
        data2.nested = data

        serialized = dumps(data2)
        data3 = loads(serialized)
        self.assertTrue(data2 == data3)
