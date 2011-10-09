#!/usr/bin/awk -f
#
# This script can be used to convert the third_party_data/belgium.poly file
# to a file in OpenAir syntax.  The belgium.poly file was downloaded from
# http://downloads.cloudmade.com/europe/western_europe/belgium
#
# Example:
#
#   ./convert_polyfile.awk ../third_party_data/belgium.poly > ../openair/belgium/belgium_cloudmade.txt


# Match a line starting a region.
/^[0-9]+[ \t]*/ {
  printf("\n");
  printf("AC C\n");
  printf("AN Belgian border\n");
  printf("AL GND\n");
  printf("AH UNLIMITED\n");
}

# Match a line with data and print it as an OpenAir DP-record.
/^[ \t]+([0-9]+[.]?[0-9]*)[ \t]+([0-9]+[.]?[0-9]*)/ {
  printf("DP %f N %f E\n", $2, $1);
}
