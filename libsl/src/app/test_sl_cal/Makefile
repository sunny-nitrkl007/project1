# Build support for CYGWIN GCC

VPATH = ../../lib/sl_cal

CFLAGS = -ansi -Wall -O -I. -I../../../include
CFLAGS += -ggdb

OBJECTS := test.o\
	model.o\
	model_cal.o\
	sl_cal_init.o\
	sl_cal_select.o\
	sl_cal_mutable_select.o\
	sl_cal_update.o\
	sl_cal_is_selected.o\
	sl_cal_mutable_create.o\
	sl_cal_read_inputs.o\
	sl_cal_get_variant_address.o\
	sl_cal_dependent_set.o\
	sl_cal_dependent_runtime_set.o\
	sl_cal_dependent_subset_set.o\
	sl_cal_all_update.o\
	sl_cal_asynch_update.o\
	sl_cal_write_outputs.o\
	sl_cal_variant_index_get.o\
	sl_cal_variant_index_init.o\
	sl_cal_variant_index_set.o\

test: $(OBJECTS) 


