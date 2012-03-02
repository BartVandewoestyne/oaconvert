[MAP]

; Name of the file to be created, excluding extension which is added
; automatically (e.g. TDB or MDX).  Cannot use period ‘.’ as well as it is
; strongly recommended to not to use space character.
;
; Note:
;   The generating script replaces this value by a map name!
FileName=SomeFileName

; The Product name.  This field is not displayed on the GPS unit.  This field is
; displayed on the product menu bar and product menu in the MapSource software.
;
; Note:
;   The generating script replaces this value by a map name!
MapsourceName=Bart's Fantastic Airspace Map

; The Area name.  This field is the second field displayed on the GPS unit under
; the "Map Information" section.  It is displayed in the MapSource software on
; the "maps" tab when the map is selected and in the Map Properties window.
MapSetName=Bart's Airspace Map Set

; The CD Set Name.  This field is not displayed on the GPS unit.  This field is
; displayed in the MapSource software when displaying the Product Information.
CDSetName=Bart's Airspace CD Set

; The software version of the CDSetName.  This field is not displayed on the
; GPS unit.  This field is displayed in the MapSource software when displaying
; the Product Information.  It will be displayed as n.nn.
;
; For example:
;
;   MapVersion=153 will be displayed as Data Version 1.53
; 
; This field can only contain numeric characters and must be three characters
; long (i.e. 000 through 999).
MapVersion=100

; The first line of the copyright text associated with the CDSetName.  This
; field is not displayed on the GPS unit.  This field is displayed in the
; MapSource software when displaying the Product Information.
Copy1=Made by Bart Vandewoestyne
Copy2=Licensed under the Creative Commons license
Copy3=Spread the word!

; Code page for the index files.  Has to be consistent with coding in all IMG
; files included into map-set.  Important when global index file is created.
; Refer to section 6 on page 64 of te cGPSmapper user manual for details.
CodePage=1252

; FID identifier used for map-set.  Has to be consistent with coding in all IMG
; files included into map-set.  Important when using lock feature of cGPSmapper.
; Refer to section 7 (on page 67) of cGPSmapper user manual for details.
;
; Family ID value.  Unique identifier for map creator.  FID value is hard-coded
; into the cGPSmapper registration to ensure that each map creator is using a
; unique value.  Some registrations are holding a range of allowed FID values.
; In this case, this value has to be defined in the header of map.
; FID=123 decimal = 7B hex
FID=123

; Product code of the map-set.  Allow creating several separate products
; (map-sets) within one FID.  This value cannot be higher than 60.  Has to be
; consistent with coding in all IMG files included into map-set.
;
; According to http://www.shanghai2006.narod.ru/eng/gps/imgtdb.html this
; number is important and i should use a number which does not appear in
; HKEY_LOCAL_MACHINE\SOFTWARE\Garmin\MapSource\Products\<ProductCode>
. and it should be more than 40.
;
; Note Bart: i think this is only used if you are using the locking feature
;            of cgpsmapper.
ProductCode=1

; ID value of the preview IMG file.  It is strongly recommended to set this
; value always to 1.
ID=1

Levels=2

; Level0 should match the BIT value for the last (empty) level set in MapEdit
; for the map.
Level0=11

; Level1 should be lower b one than level0.
Level1=10

; should be higher by one the bigger MapSource zoom or 7 depending on what less.
Zoom0=5

; Zoom1 should be higher by one than Zoom0.
Zoom1=6
[END-MAP]

; Section [FILES] contains references (filenames) of all the IMG files to be
; used to create a complete map-set.  Due to MapSource special requirements, it
; is forbidden to use the name 00000008.img for any detailed IMG map file.
[FILES]

; Note:
;   The generating script replaces this value by a unique ID for the map!
IMG=19780321.img

[END-FILES]
