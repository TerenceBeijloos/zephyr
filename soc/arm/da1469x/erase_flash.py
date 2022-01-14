import os
import flash_script_variables as fsv

erase_command='python.exe ' + fsv.sdk_path + fsv.python_script_path + 'erase_qspi.py' ' --jlink --jlink_path ' + fsv.jlink_path
print(erase_command)
os.system(erase_command)