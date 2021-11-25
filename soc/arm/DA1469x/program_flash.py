import os
import flash_script_variables as fsv

program_command='python.exe ' + fsv.sdk_path + fsv.python_script_path + 'program_qspi.py' + ' --jlink --prod_header --jlink_path ' + fsv.jlink_path + ' ' + fsv.zephyr_bin_file
os.system(program_command)