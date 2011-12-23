[MAP]

; Not important.  This is the name of the files.
FileName=SomeFileName

; Not important.  It will be shown in the listbox of MapSource available maps.
MapsourceName=Bart's Fantastic Airspace Map

; Not important.  It will be shown in tab-sheet 'Maps' and in box
; 'Map Set Name' of MapSource.
MapSetName=Bart's Airspace Map Set
CDSetName=Bart's Airspace CD Set

; Any number between 100 en 999.
MapVersion=100

; According to http://www.shanghai2006.narod.ru/eng/gps/imgtdb.html this
; number is important and i should use a number which does not appear in
; HKEY_LOCAL_MACHINE\SOFTWARE\Garmin\MapSource\Products\<ProductCode>
. and it should be more than 40.
ProductCode=1
CodePage=0
; FID=123 decimal = 7B hex
FID=123
ID=65537
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

[FILES]
IMG=19780321.img
[END-FILES]
