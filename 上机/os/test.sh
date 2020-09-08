#!/bin/bash

echo "计科1807——李宇鹏"

for ((i=0;i<5;i++));do
{
 sleep 1;echo 1>>aa && echo ”done!”
}&
done
wait
cat aa|wc -l
rm aa
