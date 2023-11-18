cmake_minimum_required(VERSION 3.16)

project(I18n)

add_custom_target(
        clean_generates
	COMMAND rm -rf en *.pot *.po~ I18n CMakeCache.txt CMakeFiles cmake_install.cmake Makefile
)

add_custom_target(
	I18n.pot
        ALL
        DEPENDS I18n.c
        COMMAND xgettext I18n.c --keyword=_ -o I18n.pot
)
add_custom_target(
	I18n.po
        ALL
	DEPENDS I18n.pot I18n.c
        COMMAND msgmerge -U I18n.po I18n.pot
)
add_custom_target(
	I18n.mo
        ALL
	DEPENDS I18n.po
        COMMAND mkdir -p en/LC_MESSAGES/
        COMMAND msgfmt I18n.po -o en/LC_MESSAGES/I18n.mo
)


add_executable(I18n I18n.c)
