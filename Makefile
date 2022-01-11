DIRS=$(wildcard week??) bonus

.PHONY: all clean force

all:
	@echo "Only \"make clean\" is supported."

clean: $(DIRS)

$(DIRS): force
	$(MAKE) -C $@ clean