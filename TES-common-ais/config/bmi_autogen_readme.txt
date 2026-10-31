=== General ===
1. Install Libre Office with the following command:

    # sudo apt-get install libreoffice

2. Copy the spreadsheet bmi_autogen_v090.ods into the project/config directory

3. Install the bmi_autogen_lib macro library.  In LibreOffice:

   Tools - Macros - Organize Macros - LibreOffice Basic - Organizer (button) - Libraries (tab) - Import - <Select TES-common-ais/config/bmi_autogen_lib/dialog.xlb> - Replace existing libraries - Insert as reference (read-only) – OK

4. Update the macro security of Libre Office:

     Tools - Options - LibreOffice - Security - Macro Security - Security Level - Low
 
     From the 'Trusted Sources' tab, you may also have to add the absolute path of the autogen_bmi.ods files to "Trusted file locations"

   Save, close, and re-open the workbook

5. To run the macro from inside LibreOffice

    Tools - Macros - Run Macro - My Macros/bmi_autogen_lib/v090/exportBmi_common

6. To make this part of the build procedure, put the following into the project Makefile:

                @echo """"
                @echo ""Generating BmiCdl and BmiJ1939 JSON files""
                @echo """"
                @soffice --invisible --nofirststartwizard --headless --norestore ""config/bmi_autogen_v090.ods"" ""macro:///bmi_autogen_lib.v090.exportBmi()""

   You will also have to update the macro security of Libre Office:

     Tools - Options - LibreOffice - Security - Macro Security - Security Level - Low
 
     From the 'Trusted Sources' tab, you may also have to add the absolute path of the autogen_bmi.ods files to "Trusted file locations"

   Save, close, and re-open the workbook

7. Be sure not to modify any content in the headers (row 1 of each sheet).  This will result in an invalid JSON rejected by the Bmi app

8. If any of the _Typedefs enums change in the TES Common code, bmi_autogen_typedef_map.csv and/or bmi_autogen_typedef_values.csv must be updated in the TES-common-ais repo.

Then update the _Typedefs tab by running the updateTypedefs macro.  This will update the data validity ranges (pull downs) for the enums

soffice --invisible --nofirststartwizard --headless --norestore "config/bmi_autogen_v090.ods" "macro:///bmi_autogen_lib.v090.updateTypedefs()"

9. If any new json attributes are added, the underlying macros will need to be updated.

10. Since the typedef/enum values are imported from a csv, multiple workbooks can be used as long as the above macros are run for each workbook.

For example, separate BmiCdl, BmiJ1939, and BmiEth workbooks can be created.  Further still, a separate workbook can be created for each machine configuration.

=== BmiJ1939 ===
1. Each worksheet must start with “BmiJ1939_PID”.  A json file will be created for each worksheet.  BmiJ1939_PID_Example should be renamed/copied as a template.

2. A corresponding “BmiJ1939_PGN” sheet must exist for each “BmiJ1939_PID” sheet.  At a minimum, it must contain PGN 61184 ($EF00); this is already provided in BmiJ1939_PGN_Example.

3. Units, RequestType, VarLengthDataType, ParameterType fields have data validation, make sure that any new rows also share the same validation rules.

4. See TES-common-ais/apps/bmiJ1939/BmiJ1939PGNCfg_Example.txt and TES-common-ais/apps/bmiJ1939/BmiJ1939PIDCfg_Example.txt for more info.

5. If BmiJ1939 is not used, either delete the two example tabs or rename them with an underscore prefix.

6. For CAT EXT IDS, set RestrAdtReadParam to 0 if read is not restricted.

=== BmiCdl ===
1. Each worksheet must start with “BmiCdl_PID”.  A json file will be created for each worksheet.  BmiCdl_PID_Example should be renamed/copied as a template.

2. A corresponding “BmiCdl_ECM” sheet must exist for each “BmiCdl_PID” sheet.  This contains the ECM header information, and all 'mid's in the BmiCdl_PID sheet must be supported.

3. parm_request_type, parameter_type, Units fields have data validation, make sure that any new rows also share the same validation rules.

4. See TES-common-ais/apps/bmiCdl/BmiCdlConfigTemplate.txt for more info.

5. If BmiCdl is not used, either delete the two example tabs or rename them with an underscore prefix.

=== BmiEth ===
1. The following combinations are supported: PID Only, SPN Only, PID and SPN.  For PIDs, each worksheet must start with “BmiEth_PID”.  For SPNs, they must start with BmiEth_SPN”  A json file will be created for each pair of worksheets.  BmiEth_PID_Example and BmiEth_PGN_Example should be renamed/copied as a template.

2. A corresponding “BmiEth_ECM” sheet must exist for each “BmiEth_PID” and/or “BmiEth_SPN” sheet.  This contains the ECM header information.

3. Several fields have data validation, make sure that any new rows also share the same validation rules by copying the existing ones.

4. See TES-common-ais/apps/BmiEthernet/BmiEthConfigTemplate.txt for more info.

5. If BmiEth is not used, either delete the two example tabs or rename them with an underscore prefix.

6. Note: “Request Period(mu)” is in units of micro seconds


=== Version History ===
0.11.0
  Add CID and SPN List column to BmiJ1939_PGN worksheet for J1939 Health.  No changes made to the macro library.
