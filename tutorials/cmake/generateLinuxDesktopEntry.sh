 #!/bin/sh
cat <<EOF
[Desktop Entry]
Version=1.2
Type=Application
Terminal=false
Name=myProgram
GenericName=myProgram
Comment=A simple example
TryExec=/usr/bin/myProgram
Exec=/usr/bin/myProgram
Categories=Education;Science;Math;
Icon=/usr/share/myProgram/icons/logo.png
EOF
