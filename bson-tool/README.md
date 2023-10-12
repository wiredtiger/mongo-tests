# BSON inspect and edit tool

This is a self-contained stand-alone tool for reading, modifying and creating [BSON](https://www.mongodb.com/basics/bson) documents.

BSON is a binary format, it can't be viewed or edited directly.
Because BSON is a superset of JSON, it's impossible to convert BSON to JSON
and back withous loss of information.
There are [tools](https://www.mongodb.com/docs/database-tools/bsondump/) and
[libraries](https://www.npmjs.com/package/bson) for converting between BSON and JSON,
but creating and editing BSON documents with them is still a challenge.

This tool allows to dump BSON documents in a nice human-readable format,
edit them and create new BSON documents.
It's guaranteed to produce exactly the same BSON result on a roud-trip.

Based on (forked from) [py-bson/bson](https://github.com/py-bson/bson) library.

## Synopsis (TL;DR)

```bash
$ bson-dump bson-example

$ bson-dump-flat bson-example

$ bson-dump-py bson-example > bson-gen.py
... edit bson-gen.py
$ python3 ./bson-gen.py
```

## Installation

`bson-tool` is a self-contained and doesn't require anything to be installed.
Just get the source to your machine:

```bash
$ git clone https://github.com/wiredtiger/mongo-tests.git
$ cd mongo-tests/bson-tool
```

or pull a single subdirectory:

```bash
$ git init mongo-tests
$ cd mongo-tests
$ git remote add origin https://github.com/wiredtiger/mongo-tests.git
$ git config core.sparseCheckout true
$ echo "bson-tool/**" >> .git/info/sparse-checkout
$ git pull --depth=1 origin master
```

## Usage

### Checking the content of a BSON file

#### In python-ish object notation:

```bash
$ bson-dump bson-example
{'md': {'ns': 'good.good',
        'options': {'uuid': UUID('aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee')},
        'indexes': [{'spec': {'v': 2, 'key': {'_id': 1}, 'name': '_id_'},
                     'ready': True,
                     'multikey': False,
                     'multikeyPaths': {'_id': b'\x00'},
                     'head': 0,
                     'prefix': -1,
                     'backgroundSecondary': False},
                    {'spec': {'v': 2,
                              'key': {'created_date': -1},
................
                     'backgroundSecondary': False,
                     'buildUUID': UUID('ffffffff-9999-8888-7777-666666666666')}],
        'prefix': -1},
 'idxIdent': {'_id_': 'good/index-12345--9876543210987654321',
              'created_date_-1': 'good/index-9828-5556667778889993331',
              'codes.code_1': 'good/index-9830-5556667778889993331',
              'good_events.created_at_-1': 'good/index-9832-5556667778889993331',
              'organization_ids': 'good/index-9834-5556667778889993331',
              'tag_ids': 'good/index-9836-5556667778889993331',
              'gray_market': 'good/index-9839-5556667778889993331'},
 'ns': 'good.good',
 'ident': 'good/collection-54321--9876543210987654321'}
```

#### In flat notation (one line per element):

```bash
$ bson-dump-flat bson-example
/md/ns: good.good
/md/options/uuid: aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee
/md/indexes/[0]/spec/v: 2
/md/indexes/[0]/spec/key/_id: 1
/md/indexes/[0]/spec/name: _id_
................
/idxIdent/organization_ids: good/index-9834-5556667778889993331
/idxIdent/tag_ids: good/index-9836-5556667778889993331
/idxIdent/gray_market: good/index-9839-5556667778889993331
/ns: good.good
/ident: good/collection-54321--9876543210987654321
```

#### As a reversible python script:

```bash
$ bson-dump-py bson-example
#!/usr/bin/env python3

import sys
sys.path.append('<INSTALL_DIR>/bson-tool')

from bson_strict import dumps
from bson_strict.types import *

with open('bson-example-out', 'wb') as file:
  file.write(dumps(
    {'md': {'ns': 'good.good',
            'options': {'uuid': BinaryUUID(UUID('aaaaaaaa-bbbb-cccc-dddd-eeeeeeeeeeee').bytes, 4)},
            'indexes': [{'spec': {'v': Int32(2),
                                  'key': {'_id': Int32(1)},
................
                  'tag_ids': 'good/index-9836-5556667778889993331',
                  'gray_market': 'good/index-9839-5556667778889993331'},
     'ns': 'good.good',
     'ident': 'good/collection-54321--9876543210987654321'}
  ))

```

### Editing a BSON file

1.  Dump the BSON file to a python script:
    ```bash
    $ bson-dump-py bson-example > bson-gen.py
    ```
2.  Edit the python script
    * Adjust the output file name
    * Add or remove elements
    * Use type notations from `bson_strict.types`
3.  Run it script to generate a new BSON:
    ```bash
    $ python3 bson-gen.py
    ```
4.  Check the result:
    ```bash
    $ diff bson-example bson-example-out
    ```
    or in text format:
    ```bash
    $ bson-dump bson-example > bson-example-text
    $ bson-dump bson-example-out > bson-example-out-text
    $ diff bson-example-text bson-example-out-text
    ```

### Creating a BSON file fron scratch

Use the following template and put your data in it.
Use types from `bson_strict.types` to specify the exact data types.

```python
#!/usr/bin/env python3

import sys
sys.path.append('<INSTALL_DIR>/bson-tool')

from bson_strict import dumps
from bson_strict.types import *

with open('bson-example-out', 'wb') as file:
  file.write(dumps(
    {'key1': 1,
     'key2': 'value2',
     'key3': {'subkey1': 1,
              'subkey2': 'value2'},
    }
  ))

