#!/usr/bin/awk -f
#
# This script can be used to convert the third_party_data/belgium.poly file
# to a file in OpenAir syntax.  The belgium.poly file was downloaded from
# http://downloads.cloudmade.com/europe/western_europe/belgium
#
# Example:
#
#   ./convert_polyfile.awk ../third_party_data/belgium.poly > ../openair/belgium/belgian_border.txt


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

  # We only keep 6 decimal places since GPSMapEdit also only
  # uses this number of decimal places.
  printf("DP %.6f N %.6f E\n", $2, $1);

  # With this alternative, we use the precision as it is specified in the
  # original datafile. 
  #printf("DP %s N %s E\n", $2, $1);
}
