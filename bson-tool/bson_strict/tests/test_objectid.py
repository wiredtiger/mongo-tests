# Copyright 2009-2015 MongoDB, Inc.
# Modifications copyright (C) 2018 Gabriel Leopoldino
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Tests for the objectid module."""

import datetime
import os
import pickle
import sys
import struct

sys.path[0:0] = [""]

from bson_strict.objectid import ObjectId, _fnv_1a_24
from bson_strict.objectid import InvalidId
from bson_strict.py3compat import PY3, _unicode
from bson_strict.tz_util import (FixedOffset,
                          utc)

if sys.version_info[:2] == (2, 6):
    import unittest2 as unittest
    from unittest2 import SkipTest
else:
    import unittest
    from unittest import SkipTest

# fnv_1a_24 tests taken from MongoDB Python Driver at https://github.com/mongodb/mongo-python-driver/commit/61850357a0e0eeec1a30e1adc0bbf7ebee807358
# Landon Curt Noll's test suite for FNV-1a32
# http://isthe.com/chongo/src/fnv/test_fnv.c
TEST = lambda x: x
TEST0 = lambda x: x + b"\x00"
R10 = lambda x: x * 10
R500 = lambda x: x * 500
fnv_test_str = [
  TEST(b""),
  TEST(b"a"),
  TEST(b"b"),
  TEST(b"c"),
  TEST(b"d"),
  TEST(b"e"),
  TEST(b"f"),
  TEST(b"fo"),
  TEST(b"foo"),
  TEST(b"foob"),
  TEST(b"fooba"),
  TEST(b"foobar"),
  TEST0(b""),
  TEST0(b"a"),
  TEST0(b"b"),
  TEST0(b"c"),
  TEST0(b"d"),
  TEST0(b"e"),
  TEST0(b"f"),
  TEST0(b"fo"),
  TEST0(b"foo"),
  TEST0(b"foob"),
  TEST0(b"fooba"),
  TEST0(b"foobar"),
  TEST(b"ch"),
  TEST(b"cho"),
  TEST(b"chon"),
  TEST(b"chong"),
  TEST(b"chongo"),
  TEST(b"chongo "),
  TEST(b"chongo w"),
  TEST(b"chongo wa"),
  TEST(b"chongo was"),
  TEST(b"chongo was "),
  TEST(b"chongo was h"),
  TEST(b"chongo was he"),
  TEST(b"chongo was her"),
  TEST(b"chongo was here"),
  TEST(b"chongo was here!"),
  TEST(b"chongo was here!\n"),
  TEST0(b"ch"),
  TEST0(b"cho"),
  TEST0(b"chon"),
  TEST0(b"chong"),
  TEST0(b"chongo"),
  TEST0(b"chongo "),
  TEST0(b"chongo w"),
  TEST0(b"chongo wa"),
  TEST0(b"chongo was"),
  TEST0(b"chongo was "),
  TEST0(b"chongo was h"),
  TEST0(b"chongo was he"),
  TEST0(b"chongo was her"),
  TEST0(b"chongo was here"),
  TEST0(b"chongo was here!"),
  TEST0(b"chongo was here!\n"),
  TEST(b"cu"),
  TEST(b"cur"),
  TEST(b"curd"),
  TEST(b"curds"),
  TEST(b"curds "),
  TEST(b"curds a"),
  TEST(b"curds an"),
  TEST(b"curds and"),
  TEST(b"curds and "),
  TEST(b"curds and w"),
  TEST(b"curds and wh"),
  TEST(b"curds and whe"),
  TEST(b"curds and whey"),
  TEST(b"curds and whey\n"),
  TEST0(b"cu"),
  TEST0(b"cur"),
  TEST0(b"curd"),
  TEST0(b"curds"),
  TEST0(b"curds "),
  TEST0(b"curds a"),
  TEST0(b"curds an"),
  TEST0(b"curds and"),
  TEST0(b"curds and "),
  TEST0(b"curds and w"),
  TEST0(b"curds and wh"),
  TEST0(b"curds and whe"),
  TEST0(b"curds and whey"),
  TEST0(b"curds and whey\n"),
  TEST(b"hi"), TEST0(b"hi"),
  TEST(b"hello"), TEST0(b"hello"),
  TEST(b"\xff\x00\x00\x01"), TEST(b"\x01\x00\x00\xff"),
  TEST(b"\xff\x00\x00\x02"), TEST(b"\x02\x00\x00\xff"),
  TEST(b"\xff\x00\x00\x03"), TEST(b"\x03\x00\x00\xff"),
  TEST(b"\xff\x00\x00\x04"), TEST(b"\x04\x00\x00\xff"),
  TEST(b"\x40\x51\x4e\x44"), TEST(b"\x44\x4e\x51\x40"),
  TEST(b"\x40\x51\x4e\x4a"), TEST(b"\x4a\x4e\x51\x40"),
  TEST(b"\x40\x51\x4e\x54"), TEST(b"\x54\x4e\x51\x40"),
  TEST(b"127.0.0.1"), TEST0(b"127.0.0.1"),
  TEST(b"127.0.0.2"), TEST0(b"127.0.0.2"),
  TEST(b"127.0.0.3"), TEST0(b"127.0.0.3"),
  TEST(b"64.81.78.68"), TEST0(b"64.81.78.68"),
  TEST(b"64.81.78.74"), TEST0(b"64.81.78.74"),
  TEST(b"64.81.78.84"), TEST0(b"64.81.78.84"),
  TEST(b"feedface"), TEST0(b"feedface"),
  TEST(b"feedfacedaffdeed"), TEST0(b"feedfacedaffdeed"),
  TEST(b"feedfacedeadbeef"), TEST0(b"feedfacedeadbeef"),
  TEST(b"line 1\nline 2\nline 3"),
  TEST(b"chongo <Landon Curt Noll> /\\../\\"),
  TEST0(b"chongo <Landon Curt Noll> /\\../\\"),
  TEST(b"chongo (Landon Curt Noll) /\\../\\"),
  TEST0(b"chongo (Landon Curt Noll) /\\../\\"),
  TEST(b"http://antwrp.gsfc.nasa.gov/apod/astropix.html"),
  TEST(b"http://en.wikipedia.org/wiki/Fowler_Noll_Vo_hash"),
  TEST(b"http://epod.usra.edu/"),
  TEST(b"http://exoplanet.eu/"),
  TEST(b"http://hvo.wr.usgs.gov/cam3/"),
  TEST(b"http://hvo.wr.usgs.gov/cams/HMcam/"),
  TEST(b"http://hvo.wr.usgs.gov/kilauea/update/deformation.html"),
  TEST(b"http://hvo.wr.usgs.gov/kilauea/update/images.html"),
  TEST(b"http://hvo.wr.usgs.gov/kilauea/update/maps.html"),
  TEST(b"http://hvo.wr.usgs.gov/volcanowatch/current_issue.html"),
  TEST(b"http://neo.jpl.nasa.gov/risk/"),
  TEST(b"http://norvig.com/21-days.html"),
  TEST(b"http://primes.utm.edu/curios/home.php"),
  TEST(b"http://slashdot.org/"),
  TEST(b"http://tux.wr.usgs.gov/Maps/155.25-19.5.html"),
  TEST(b"http://volcano.wr.usgs.gov/kilaueastatus.php"),
  TEST(b"http://www.avo.alaska.edu/activity/Redoubt.php"),
  TEST(b"http://www.dilbert.com/fast/"),
  TEST(b"http://www.fourmilab.ch/gravitation/orbits/"),
  TEST(b"http://www.fpoa.net/"),
  TEST(b"http://www.ioccc.org/index.html"),
  TEST(b"http://www.isthe.com/cgi-bin/number.cgi"),
  TEST(b"http://www.isthe.com/chongo/bio.html"),
  TEST(b"http://www.isthe.com/chongo/index.html"),
  TEST(b"http://www.isthe.com/chongo/src/calc/lucas-calc"),
  TEST(b"http://www.isthe.com/chongo/tech/astro/venus2004.html"),
  TEST(b"http://www.isthe.com/chongo/tech/astro/vita.html"),
  TEST(b"http://www.isthe.com/chongo/tech/comp/c/expert.html"),
  TEST(b"http://www.isthe.com/chongo/tech/comp/calc/index.html"),
  TEST(b"http://www.isthe.com/chongo/tech/comp/fnv/index.html"),
  TEST(b"http://www.isthe.com/chongo/tech/math/number/howhigh.html"),
  TEST(b"http://www.isthe.com/chongo/tech/math/number/number.html"),
  TEST(b"http://www.isthe.com/chongo/tech/math/prime/mersenne.html"),
  TEST(b"http://www.isthe.com/chongo/tech/math/prime/mersenne.html#largest"),
  TEST(b"http://www.lavarnd.org/cgi-bin/corpspeak.cgi"),
  TEST(b"http://www.lavarnd.org/cgi-bin/haiku.cgi"),
  TEST(b"http://www.lavarnd.org/cgi-bin/rand-none.cgi"),
  TEST(b"http://www.lavarnd.org/cgi-bin/randdist.cgi"),
  TEST(b"http://www.lavarnd.org/index.html"),
  TEST(b"http://www.lavarnd.org/what/nist-test.html"),
  TEST(b"http://www.macosxhints.com/"),
  TEST(b"http://www.mellis.com/"),
  TEST(b"http://www.nature.nps.gov/air/webcams/parks/havoso2alert/havoalert.cfm"),
  TEST(b"http://www.nature.nps.gov/air/webcams/parks/havoso2alert/timelines_24.cfm"),
  TEST(b"http://www.paulnoll.com/"),
  TEST(b"http://www.pepysdiary.com/"),
  TEST(b"http://www.sciencenews.org/index/home/activity/view"),
  TEST(b"http://www.skyandtelescope.com/"),
  TEST(b"http://www.sput.nl/~rob/sirius.html"),
  TEST(b"http://www.systemexperts.com/"),
  TEST(b"http://www.tq-international.com/phpBB3/index.php"),
  TEST(b"http://www.travelquesttours.com/index.htm"),
  TEST(b"http://www.wunderground.com/global/stations/89606.html"),
  TEST(R10(b"21701")),
  TEST(R10(b"M21701")),
  TEST(R10(b"2^21701-1")),
  TEST(R10(b"\x54\xc5")),
  TEST(R10(b"\xc5\x54")),
  TEST(R10(b"23209")),
  TEST(R10(b"M23209")),
  TEST(R10(b"2^23209-1")),
  TEST(R10(b"\x5a\xa9")),
  TEST(R10(b"\xa9\x5a")),
  TEST(R10(b"391581216093")),
  TEST(R10(b"391581*2^216093-1")),
  TEST(R10(b"\x05\xf9\x9d\x03\x4c\x81")),
  TEST(R10(b"FEDCBA9876543210")),
  TEST(R10(b"\xfe\xdc\xba\x98\x76\x54\x32\x10")),
  TEST(R10(b"EFCDAB8967452301")),
  TEST(R10(b"\xef\xcd\xab\x89\x67\x45\x23\x01")),
  TEST(R10(b"0123456789ABCDEF")),
  TEST(R10(b"\x01\x23\x45\x67\x89\xab\xcd\xef")),
  TEST(R10(b"1032547698BADCFE")),
  TEST(R10(b"\x10\x32\x54\x76\x98\xba\xdc\xfe")),
  TEST(R500(b"\x00")),
  TEST(R500(b"\x07")),
  TEST(R500(b"~")),
  TEST(R500(b"\x7f"))
]

fnv1a_24_vector = {
    fnv_test_str[0]: 0x1c9d44,
    fnv_test_str[1]: 0x0c29c8,
    fnv_test_str[2]: 0x0c2d02,
    fnv_test_str[3]: 0x0c2cb4,
    fnv_test_str[4]: 0x0c2492,
    fnv_test_str[5]: 0x0c2200,
    fnv_test_str[6]: 0x0c277a,
    fnv_test_str[7]: 0x22e820,
    fnv_test_str[8]: 0xf37e7e,
    fnv_test_str[9]: 0x5076d0,
    fnv_test_str[10]: 0xaaa1b3,
    fnv_test_str[11]: 0x9cf9d7,
    fnv_test_str[12]: 0x0c5d1a,
    fnv_test_str[13]: 0x24d06f,
    fnv_test_str[14]: 0x2c3fe2,
    fnv_test_str[15]: 0x29c561,
    fnv_test_str[16]: 0x1d61b0,
    fnv_test_str[17]: 0x1ae633,
    fnv_test_str[18]: 0x2255de,
    fnv_test_str[19]: 0xf39f58,
    fnv_test_str[20]: 0x50ac14,
    fnv_test_str[21]: 0xab3aa7,
    fnv_test_str[22]: 0x9c4c6f,
    fnv_test_str[23]: 0x1c9eb4,
    fnv_test_str[24]: 0x299f11,
    fnv_test_str[25]: 0x85801c,
    fnv_test_str[26]: 0x29778b,
    fnv_test_str[27]: 0x46b985,
    fnv_test_str[28]: 0x564ec0,
    fnv_test_str[29]: 0xdd5c0c,
    fnv_test_str[30]: 0x77eded,
    fnv_test_str[31]: 0xca9677,
    fnv_test_str[32]: 0xeb9b9a,
    fnv_test_str[33]: 0xe67a30,
    fnv_test_str[34]: 0xd32f6a,
    fnv_test_str[35]: 0x743fc8,
    fnv_test_str[36]: 0x006376,
    fnv_test_str[37]: 0x9c99cb,
    fnv_test_str[38]: 0x8524b9,
    fnv_test_str[39]: 0x993001,
    fnv_test_str[40]: 0x85c7d6,
    fnv_test_str[41]: 0x29fe8b,
    fnv_test_str[42]: 0x469249,
    fnv_test_str[43]: 0x56698e,
    fnv_test_str[44]: 0xdd8e4c,
    fnv_test_str[45]: 0x787611,
    fnv_test_str[46]: 0xca6243,
    fnv_test_str[47]: 0xeaf0e4,
    fnv_test_str[48]: 0xe648b0,
    fnv_test_str[49]: 0xd355aa,
    fnv_test_str[50]: 0x740522,
    fnv_test_str[51]: 0x004d4e,
    fnv_test_str[52]: 0x9c09a7,
    fnv_test_str[53]: 0x84f129,
    fnv_test_str[54]: 0x993a9d,
    fnv_test_str[55]: 0x27dfcd,
    fnv_test_str[56]: 0x298129,
    fnv_test_str[57]: 0x5637c9,
    fnv_test_str[58]: 0xb9140f,
    fnv_test_str[59]: 0x5bf5a7,
    fnv_test_str[60]: 0xc42805,
    fnv_test_str[61]: 0xcc0e97,
    fnv_test_str[62]: 0x3b4c5d,
    fnv_test_str[63]: 0x59f0a7,
    fnv_test_str[64]: 0x94de0b,
    fnv_test_str[65]: 0x5a0a72,
    fnv_test_str[66]: 0xbee56f,
    fnv_test_str[67]: 0x8363fd,
    fnv_test_str[68]: 0xd5346c,
    fnv_test_str[69]: 0xa14715,
    fnv_test_str[70]: 0x56b1b5,
    fnv_test_str[71]: 0xb8e81f,
    fnv_test_str[72]: 0x5b4a33,
    fnv_test_str[73]: 0xc3f6c5,
    fnv_test_str[74]: 0xcc3f23,
    fnv_test_str[75]: 0x3b0a59,
    fnv_test_str[76]: 0x59c467,
    fnv_test_str[77]: 0x9510cb,
    fnv_test_str[78]: 0x59bdc4,
    fnv_test_str[79]: 0xbf0b0f,
    fnv_test_str[80]: 0x83ff3d,
    fnv_test_str[81]: 0xd54252,
    fnv_test_str[82]: 0xa156e9,
    fnv_test_str[83]: 0xe2d780,
    fnv_test_str[84]: 0x3af6f2,
    fnv_test_str[85]: 0xd234c0,
    fnv_test_str[86]: 0x9f2ce4,
    fnv_test_str[87]: 0x935133,
    fnv_test_str[88]: 0x8fb8a9,
    fnv_test_str[89]: 0x69f34b,
    fnv_test_str[90]: 0x8fb375,
    fnv_test_str[91]: 0xef1266,
    fnv_test_str[92]: 0x8fb585,
    fnv_test_str[93]: 0xc3bfd1,
    fnv_test_str[94]: 0x8fb031,
    fnv_test_str[95]: 0xe4d46f,
    fnv_test_str[96]: 0x17906a,
    fnv_test_str[97]: 0x0bfece,
    fnv_test_str[97]: 0x0bfece,
    fnv_test_str[98]: 0x178d02,
    fnv_test_str[99]: 0xaddad9,
    fnv_test_str[100]: 0x17a9ca,
    fnv_test_str[101]: 0x2633a1,
    fnv_test_str[102]: 0xa3d116,
    fnv_test_str[103]: 0xe2328d,
    fnv_test_str[104]: 0xa3cf8c,
    fnv_test_str[105]: 0xdfb740,
    fnv_test_str[106]: 0xa3cdfe,
    fnv_test_str[107]: 0xdd3d03,
    fnv_test_str[108]: 0x5636ba,
    fnv_test_str[109]: 0xb80830,
    fnv_test_str[110]: 0x53e841,
    fnv_test_str[111]: 0x16b9a9,
    fnv_test_str[112]: 0x5b8948,
    fnv_test_str[113]: 0x1a202b,
    fnv_test_str[114]: 0x88b139,
    fnv_test_str[115]: 0x2f0186,
    fnv_test_str[116]: 0x364109,
    fnv_test_str[117]: 0x69b55d,
    fnv_test_str[118]: 0x7604b9,
    fnv_test_str[119]: 0xc8bd3c,
    fnv_test_str[120]: 0xb4eab4,
    fnv_test_str[121]: 0x4e927c,
    fnv_test_str[122]: 0xb140dd,
    fnv_test_str[123]: 0x1b25e1,
    fnv_test_str[124]: 0xbb59c8,
    fnv_test_str[125]: 0x524a34,
    fnv_test_str[126]: 0x16ef98,
    fnv_test_str[127]: 0x648bd3,
    fnv_test_str[128]: 0xa4bc83,
    fnv_test_str[129]: 0x53ae47,
    fnv_test_str[130]: 0x302859,
    fnv_test_str[131]: 0x6deda7,
    fnv_test_str[132]: 0x36db15,
    fnv_test_str[133]: 0x9d33fc,
    fnv_test_str[134]: 0xbb6ce2,
    fnv_test_str[135]: 0xf83893,
    fnv_test_str[136]: 0x08bf51,
    fnv_test_str[137]: 0xcc8e5f,
    fnv_test_str[138]: 0xe20f9f,
    fnv_test_str[139]: 0xe97f2e,
    fnv_test_str[140]: 0x37b27b,
    fnv_test_str[141]: 0x9e874a,
    fnv_test_str[142]: 0xe63f5a,
    fnv_test_str[143]: 0xb50b11,
    fnv_test_str[144]: 0xd678e6,
    fnv_test_str[145]: 0xd5b723,
    fnv_test_str[146]: 0x450bb7,
    fnv_test_str[147]: 0x72d79d,
    fnv_test_str[148]: 0x06679c,
    fnv_test_str[149]: 0x52e15c,
    fnv_test_str[150]: 0x9664f7,
    fnv_test_str[151]: 0x3258b6,
    fnv_test_str[152]: 0xed6ea7,
    fnv_test_str[153]: 0x7d7ce2,
    fnv_test_str[154]: 0xc71ba1,
    fnv_test_str[155]: 0x84f14b,
    fnv_test_str[156]: 0x8ecf2e,
    fnv_test_str[157]: 0x94f673,
    fnv_test_str[158]: 0x970112,
    fnv_test_str[159]: 0x6e172a,
    fnv_test_str[160]: 0xf8f6e7,
    fnv_test_str[161]: 0xf58843,
    fnv_test_str[162]: 0x17b6b2,
    fnv_test_str[163]: 0xad4cfb,
    fnv_test_str[164]: 0x256811,
    fnv_test_str[165]: 0xb18dd8,
    fnv_test_str[166]: 0x61c153,
    fnv_test_str[167]: 0x47d20d,
    fnv_test_str[168]: 0x8b689f,
    fnv_test_str[169]: 0xd2a40b,
    fnv_test_str[170]: 0x549b0a,
    fnv_test_str[171]: 0xe1b55b,
    fnv_test_str[172]: 0x0cd3d1,
    fnv_test_str[173]: 0x471605,
    fnv_test_str[174]: 0x5eef10,
    fnv_test_str[175]: 0xed3629,
    fnv_test_str[176]: 0x624952,
    fnv_test_str[177]: 0x9b8688,
    fnv_test_str[178]: 0x15e25f,
    fnv_test_str[179]: 0xa98d05,
    fnv_test_str[180]: 0xdf8bcc,
    fnv_test_str[181]: 0x1e9051,
    fnv_test_str[182]: 0x3f70db,
    fnv_test_str[183]: 0x95aedb,
    fnv_test_str[184]: 0xa7f7d7,
    fnv_test_str[185]: 0x3bc660,
    fnv_test_str[186]: 0x610967,
    fnv_test_str[187]: 0x157785,
    fnv_test_str[188]: 0x2b2800,
    fnv_test_str[189]: 0x8239ef,
    fnv_test_str[190]: 0x5869f5,
    fnv_test_str[191]: 0x415c76,
    fnv_test_str[192]: 0xe4ff6f,
    fnv_test_str[193]: 0xb7977d,
    fnv_test_str[194]: 0xa43a7b,
    fnv_test_str[195]: 0xb3be1e,
    fnv_test_str[196]: 0x777aaf,
    fnv_test_str[197]: 0x21c38a,
    fnv_test_str[198]: 0x9d0839,
    fnv_test_str[199]: 0x823d2f,
    fnv_test_str[200]: 0xa27250,
    fnv_test_str[201]: 0xc5c656,
    fnv_test_str[202]: 0x3b0800,
}


def oid(x):
    return ObjectId()

def oid_generated_on_client(oid):
    """Is this process's PID in this ObjectId?"""
    pid_from_doc = struct.unpack(">H", oid.binary[7:9])[0]
    return (os.getpid() % 0xFFFF) == pid_from_doc

class TestObjectId(unittest.TestCase):
    def test_creation(self):
        self.assertRaises(TypeError, ObjectId, 4)
        self.assertRaises(TypeError, ObjectId, 175.0)
        self.assertRaises(TypeError, ObjectId, {"test": 4})
        self.assertRaises(TypeError, ObjectId, ["something"])
        self.assertRaises(InvalidId, ObjectId, "")
        self.assertRaises(InvalidId, ObjectId, "12345678901")
        self.assertRaises(InvalidId, ObjectId, "1234567890123")
        self.assertTrue(ObjectId())
        self.assertTrue(ObjectId(b"123456789012"))
        a = ObjectId()
        self.assertTrue(ObjectId(a))

    def test_fnv_1a_24(self):
        for key in fnv1a_24_vector:
            self.assertEqual(_fnv_1a_24(key), fnv1a_24_vector[key])

    def test_unicode(self):
        a = ObjectId()
        self.assertEqual(a, ObjectId(_unicode(a)))
        self.assertEqual(ObjectId("123456789012123456789012"),
                         ObjectId(u"123456789012123456789012"))
        self.assertRaises(InvalidId, ObjectId, u"hello")

    def test_from_hex(self):
        ObjectId("123456789012123456789012")
        self.assertRaises(InvalidId, ObjectId, "123456789012123456789G12")
        self.assertRaises(InvalidId, ObjectId, u"123456789012123456789G12")

    def test_repr_str(self):
        self.assertEqual(repr(ObjectId("1234567890abcdef12345678")),
                         "ObjectId('1234567890abcdef12345678')")
        self.assertEqual(str(ObjectId("1234567890abcdef12345678")),
                         "1234567890abcdef12345678")
        self.assertEqual(str(ObjectId(b"123456789012")),
                         "313233343536373839303132")
        self.assertEqual(ObjectId("1234567890abcdef12345678").binary,
                         b'\x124Vx\x90\xab\xcd\xef\x124Vx')
        self.assertEqual(str(ObjectId(b'\x124Vx\x90\xab\xcd\xef\x124Vx')),
                         "1234567890abcdef12345678")

    def test_equality(self):
        a = ObjectId()
        self.assertEqual(a, ObjectId(a))
        self.assertEqual(ObjectId(b"123456789012"),
                         ObjectId(b"123456789012"))
        self.assertNotEqual(ObjectId(), ObjectId())
        self.assertNotEqual(ObjectId(b"123456789012"), b"123456789012")

        # Explicitly test inequality
        self.assertFalse(a != ObjectId(a))
        self.assertFalse(ObjectId(b"123456789012") !=
                         ObjectId(b"123456789012"))

    def test_binary_str_equivalence(self):
        a = ObjectId()
        self.assertEqual(a, ObjectId(a.binary))
        self.assertEqual(a, ObjectId(str(a)))

    def test_pid(self):
        self.assertTrue(oid_generated_on_client(ObjectId()))

    def test_generation_time(self):
        d1 = datetime.datetime.utcnow()
        d2 = ObjectId().generation_time

        self.assertEqual(utc, d2.tzinfo)
        d2 = d2.replace(tzinfo=None)
        self.assertTrue(d2 - d1 < datetime.timedelta(seconds=2))

    def test_from_datetime(self):
        if 'PyPy 1.8.0' in sys.version:
            # See https://bugs.pypy.org/issue1092
            raise SkipTest("datetime.timedelta is broken in pypy 1.8.0")
        d = datetime.datetime.utcnow()
        d = d - datetime.timedelta(microseconds=d.microsecond)
        oid = ObjectId.from_datetime(d)
        self.assertEqual(d, oid.generation_time.replace(tzinfo=None))
        self.assertEqual("0" * 16, str(oid)[8:])

        aware = datetime.datetime(1993, 4, 4, 2,
                                  tzinfo=FixedOffset(555, "SomeZone"))
        as_utc = (aware - aware.utcoffset()).replace(tzinfo=utc)
        oid = ObjectId.from_datetime(aware)
        self.assertEqual(as_utc, oid.generation_time)

    def test_pickling(self):
        orig = ObjectId()
        for protocol in [0, 1, 2, -1]:
            pkl = pickle.dumps(orig, protocol=protocol)
            self.assertEqual(orig, pickle.loads(pkl))

    def test_pickle_backwards_compatability(self):
        # This string was generated by pickling an ObjectId in pymongo
        # version 1.9
        pickled_with_1_9 = (
            b"ccopy_reg\n_reconstructor\np0\n"
            b"(cbson.objectid\nObjectId\np1\nc__builtin__\n"
            b"object\np2\nNtp3\nRp4\n"
            b"(dp5\nS'_ObjectId__id'\np6\n"
            b"S'M\\x9afV\\x13v\\xc0\\x0b\\x88\\x00\\x00\\x00'\np7\nsb.")

        # We also test against a hardcoded "New" pickle format so that we
        # make sure we're backward compatible with the current version in
        # the future as well.
        pickled_with_1_10 = (
            b"ccopy_reg\n_reconstructor\np0\n"
            b"(cbson.objectid\nObjectId\np1\nc__builtin__\n"
            b"object\np2\nNtp3\nRp4\n"
            b"S'M\\x9afV\\x13v\\xc0\\x0b\\x88\\x00\\x00\\x00'\np5\nb.")

        if PY3:
            # Have to load using 'latin-1' since these were pickled in python2.x.
            oid_1_9 = pickle.loads(pickled_with_1_9, encoding='latin-1')
            oid_1_10 = pickle.loads(pickled_with_1_10, encoding='latin-1')
        else:
            oid_1_9 = pickle.loads(pickled_with_1_9)
            oid_1_10 = pickle.loads(pickled_with_1_10)

        self.assertEqual(oid_1_9, ObjectId("4d9a66561376c00b88000000"))
        self.assertEqual(oid_1_9, oid_1_10)

    def test_is_valid(self):
        self.assertFalse(ObjectId.is_valid(None))
        self.assertFalse(ObjectId.is_valid(4))
        self.assertFalse(ObjectId.is_valid(175.0))
        self.assertFalse(ObjectId.is_valid({"test": 4}))
        self.assertFalse(ObjectId.is_valid(["something"]))
        self.assertFalse(ObjectId.is_valid(""))
        self.assertFalse(ObjectId.is_valid("12345678901"))
        self.assertFalse(ObjectId.is_valid("1234567890123"))

        self.assertTrue(ObjectId.is_valid(b"123456789012"))
        self.assertTrue(ObjectId.is_valid("123456789012123456789012"))

if __name__ == "__main__":
    unittest.main()
