#!/bin/bash

OA2PM_ROOTDIR=~/Dropbox/MyProjects/oaconvert

AIRSPACES=${OA2PM_ROOTDIR}/airspaces/*.txt
cat ${AIRSPACES} > ${OA2PM_ROOTDIR}/airspaces/belgium.TXT

${OA2PM_ROOTDIR}/src/oaconvert ${OA2PM_ROOTDIR}/airspaces/belgium.TXT > ${OA2PM_ROOTDIR}/airspaces/belgium.mp
