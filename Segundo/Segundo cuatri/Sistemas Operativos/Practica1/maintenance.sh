#!/bin/bash

dirs = "/home /etc /var/www /opt"
path = "/backup"

mkdir -p "$path"

fecha = $(date + "%Y-%m-%d")

for dir in $dirs; do
    destiny = "$path/$date-$(basename "$dir")"
    if [ -d "$destiny"]; then
        echo "$destiny exists, no copy"
    else
        cp -r "$dir" "$destiny"
        echo "backup $dir completed in $destiny"
    fi
done

find $path -mindepth 1 -maxdepth 1 -type d -mtime +7 -exec rm -rf {}

find /var/log -type f -name "*.log" -mtime +7 -exec rm -f {} \;

echo "Maintenance done"