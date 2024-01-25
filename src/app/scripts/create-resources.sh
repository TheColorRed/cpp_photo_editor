# Change directory to current directory
cd "$(dirname "$0")"
cd ..

echo $PWD

# Create the compiled resources c file
glib-compile-resources \
  --c-name=app \
  --generate-source=resources.c \
  resources.xml

# Create the compiled resources h file
glib-compile-resources \
  --c-name=app \
  --generate-header=resources.h \
  resources.xml

# glib-compile-resources \
#   --c-name=app \
#   resources.xml

# glib-compile-resources \
#   --generate-dependencies \
#   resources.xml
