#!/bin/bash

FROM=UTF-8
TO=GBK
ICONV="iconv -f $FROM -t $TO"

SRC=.
DEST=converted

rm -rf $DEST
mkdir $DEST

cp $SRC/*.{c,h,win} $DEST

cd $DEST

find . -type f -name '*' | while read fn; do
    cp ${fn} ${fn}.bak
    $ICONV < ${fn}.bak  > ${fn}
    rm ${fn}.bak
    
    sed -i 's/$/\r/' ${fn}
done
