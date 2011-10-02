#!/bin/bash

OA2PM_ROOTDIR=~/Dropbox/MyProjects/oa2pm

AIRSPACES=${OA2PM_ROOTDIR}/airspaces/*.txt
cat ${AIRSPACES} > ${OA2PM_ROOTDIR}/airspaces/belgium.TXT

${OA2PM_ROOTDIR}/src/oa2pm ${OA2PM_ROOTDIR}/airspaces/belgium.TXT > ${OA2PM_ROOTDIR}/airspaces/belgium.mp
