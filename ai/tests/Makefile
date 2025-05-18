##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile
##

PYTEST     =   pytest

COVFLAGS   =   coverage run -m

OMIT       =   --omit=*__init__.py,../src/main.py

SRC_DIR    =   ../src/

all: tests coverage

tests:
	@$(PYTEST) -rA *.py

coverage:
	@$(COVFLAGS) $(PYTEST) *.py
	@coverage html

clean:
	@find . -name "__pycache__" -exec rm -r {} +
	@find . -name "*.pyc" -delete
	@$(RM) -r .pytest_cache
	@$(RM) -r htmlcov
	@$(RM) .coverage

.PHONY: all tests coverage clean
