#!/usr/bin/env python

from unittest import TestCase

import bson_strict


class TestBoolean(TestCase):
    def test_false_value(self):
        data = {"key": False}
        serialized = bson_strict.dumps(data)
        deserialized = bson_strict.loads(serialized)

        self.assertIsInstance(deserialized["key"], bool)
        self.assertFalse(deserialized["key"])
        self.assertTrue(serialized == b'\x0b\x00\x00\x00\x08key\x00\x00\x00')

    def test_true_value(self):
        data = {"key": True}
        serialized = bson_strict.dumps(data)
        deserialized = bson_strict.loads(serialized)

        self.assertIsInstance(deserialized["key"], bool)
        self.assertTrue(deserialized["key"])
        self.assertTrue(serialized == b'\x0b\x00\x00\x00\x08key\x00\x01\x00')
