#ifndef MEAL_IO_H
#define MEAL_IO_H

#define ENTRY_FORMAT_OUT "(%ld|%s|%s|%d|%d)\n"
#define ENTRY_FORMAT_IN  "(%ld|%65[^|]|%257[^|]|%d|%d)\n"

void write_changes(Entries *entries);
void read_file(Entries *entries);

#endif
