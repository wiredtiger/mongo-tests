echo "entropy = [" > data.py
for i in {1..10240}; do
str=`< /dev/urandom tr -dc _A-Z-a-z-0-9 | head -c${1:-100} `
echo "    \"$str\"" >> data.py
done
echo "]" >> data.py
