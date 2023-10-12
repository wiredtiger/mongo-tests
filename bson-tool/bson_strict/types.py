from uuid import UUID
from binascii import b2a_hex


class Int32:
    """
    A signed integer with a 32-bit fixed width.
    """

    def __init__(self, value):
        if value < -2 ** 31 or value > 2 ** 31 - 1:
            raise ValueError('value {} cannot be represented in int32'.format(value))
        self._value = value

    def get_value(self):
        return self._value

    def __str__(self):
        return str(self._value)

    def __repr__(self):
        return f'Int32({self._value})'


class Int64:
    """
    A signed integer with a 64-bit fixed width.
    """

    def __init__(self, value):
        if value < -2 ** 63 or value > 2 ** 63 - 1:
            raise ValueError('value {} cannot be represented in int32'.format(value))
        self._value = value

    def get_value(self):
        return self._value

    def __str__(self):
        return str(self._value)

    def __repr__(self):
        return f'Int64({self._value})'


class UInt64:
    """
    An unsigned integer with a 64-bit fixed width.
    """

    def __init__(self, value):
        if value < 0 or value > 2 ** 64 - 1:
            raise ValueError('value {} cannot be represented in uint32'.format(value))
        self._value = value

    def get_value(self):
        return self._value

    def __str__(self):
        return str(self._value)

    def __repr__(self):
        return f'UInt64({self._value})'


class OID:
    """
    BSON Object ID
    """
    def __init__(self, data):
        self.data = UUID(bytes=data)

    def get_value(self):
        return self.data

    def __str__(self):
        return b2a_hex(self.data)

    def __repr__(self):
        return f'OID({repr(self.data)})'


class Binary:
    """
    A sequence of bytes.
    """
    def __init__(self, data, subtype):
        self.data = data
        self.subtype = subtype

    @property
    def bytes(self):
        return self.data

    def get_value(self):
        return self.data

    def __str__(self):
        return str(self.data)

    def __repr__(self):
        return f'Binary({repr(self.data)}, {self.subtype})'


class BinaryUUID(Binary):
    """
    A UUID subtype of Binary.
    """
    def __init__(self, data, subtype):
        self.data = UUID(bytes=data)
        self.subtype = subtype

    @property
    def bytes(self):
        return self.data.bytes

    def get_value(self):
        return self.data.bytes

    def __str__(self):
        return str(self.data)

    def __repr__(self):
        return f'BinaryUUID({repr(self.data)}.bytes, {self.subtype})'

