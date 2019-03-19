#!/bin/sh
set -e

#Clean out
rm -rf build/*

#Generate build files
meson --prefix=$PWD/build/opene2140.app --bindir=Contents/MacOS build

#Generate extra files
cat <<EOF > build/Info.plist
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple Computer//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
	<key>CFBundleDevelopmentRegion</key>
	<string>English</string>
	<key>CFBundleExecutable</key>
	<string>opene2140</string>
	<key>CFBundleGetInfoString</key>
	<string></string>
	<key>CFBundleIconFile</key>
	<string></string>
	<key>CFBundleIdentifier</key>
	<string></string>
	<key>CFBundleInfoDictionaryVersion</key>
	<string>6.0</string>
	<key>CFBundleLongVersionString</key>
	<string></string>
	<key>CFBundleName</key>
	<string></string>
	<key>CFBundlePackageType</key>
	<string>APPL</string>
	<key>CFBundleShortVersionString</key>
	<string></string>
	<key>CFBundleSignature</key>
	<string>????</string>
	<key>CFBundleVersion</key>
	<string></string>
	<key>CSResourcesFileMapped</key>
	<true/>
	<key>NSHumanReadableCopyright</key>
	<string></string>
</dict>
</plist>
EOF

#MAKE!
cd build
ninja