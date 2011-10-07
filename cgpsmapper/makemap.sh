#!/bin/bash

cp ../openair/belgium/belgium.mp .
cgpsmapper -l ac belgium.mp
cgpsmapper -l pv mypreview.mp
