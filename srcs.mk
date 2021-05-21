# Sources
SRCDIR = src

SRCS = $(addprefix $(SRCDIR)/,\
	$(addprefix env/,\
		env.c\
		env_get.c\
		env_set.c\
	)\
	main.c\
	$(addprefix term/,\
		caps.c\
		caps_goto.c\
		caps_utils.c\
		clear.c\
		clip.c\
		control.c\
		control_line.c\
		cursor.c\
		cursor_jmp.c\
		hist.c\
		hist_cursor.c\
		init.c\
		keybind.c\
		line.c\
		line_edit.c\
		line_put.c\
		read.c\
		read_caps.c\
		read_csi.c\
		read_esc.c\
		select.c\
		select_jmp.c\
		term.c\
		write.c\
	)\
)
