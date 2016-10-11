for t in $(seq 5); do
    mongo --eval "
        x = ''
        for (var i=0; i<800; i++)
            x += 'x'
        docs = []
        for (var i=0; i<1000; i++)
            docs.push({x:x})
        ops = [{
            op: 'insert',
            ns: 'test.c' + '$t',
            doc: docs,
        }]
        res = benchRun({
            ops: ops,
            seconds: 10000,
            parallel: 1
        })
    " >> results.txt &
done

wait
