/* doc.c -- Generated structure containing function names and doc strings.

   This file was automatically made from various source files with the
   command `..//info/makedoc'.
   DO NOT EDIT THIS FILE, only `..//info/makedoc.c'.
   Source files groveled to make this file include:

	../../info/session.c
	../../info/echo-area.c
	../../info/infodoc.c
	../../info/m-x.c
	../../info/indices.c
	../../info/nodemenu.c
	../../info/footnotes.c
	../../info/variables.c

   An entry in the array FUNCTION_DOC_ARRAY is made for each command
   found in the above files; each entry consists of a function pointer,
   a string which is the user-visible name of the function,
   and a string which documents its purpose. */

#include "info.h"
#include "window.h"
#include "funs.h"

FUNCTION_DOC function_doc_array[] = {

/* Commands found in "../../info/session.c". */
   { (VFunction *)info_all_files, "all-files", (FUNCTION_KEYSEQ *)0, "Show all matching files" },
   { (VFunction *)info_next_line, "next-line", (FUNCTION_KEYSEQ *)0, "Move down to the next line" },
   { (VFunction *)info_prev_line, "prev-line", (FUNCTION_KEYSEQ *)0, "Move up to the previous line" },
   { (VFunction *)info_move_to_window_line, "move-to-window-line", (FUNCTION_KEYSEQ *)0, "Move the cursor to a specific line of the window" },
   { (VFunction *)info_end_of_line, "end-of-line", (FUNCTION_KEYSEQ *)0, "Move to the end of the line" },
   { (VFunction *)info_beginning_of_line, "beginning-of-line", (FUNCTION_KEYSEQ *)0, "Move to the start of the line" },
   { (VFunction *)info_forward_char, "forward-char", (FUNCTION_KEYSEQ *)0, "Move forward a character" },
   { (VFunction *)info_backward_char, "backward-char", (FUNCTION_KEYSEQ *)0, "Move backward a character" },
   { (VFunction *)info_forward_word, "forward-word", (FUNCTION_KEYSEQ *)0, "Move forward a word" },
   { (VFunction *)info_backward_word, "backward-word", (FUNCTION_KEYSEQ *)0, "Move backward a word" },
   { (VFunction *)info_beginning_of_node, "beginning-of-node", (FUNCTION_KEYSEQ *)0, "Move to the start of this node" },
   { (VFunction *)info_end_of_node, "end-of-node", (FUNCTION_KEYSEQ *)0, "Move to the end of this node" },
   { (VFunction *)info_scroll_forward, "scroll-forward", (FUNCTION_KEYSEQ *)0, "Scroll forward in this window" },
   { (VFunction *)info_scroll_backward, "scroll-backward", (FUNCTION_KEYSEQ *)0, "Scroll backward in this window" },
   { (VFunction *)info_scroll_forward_set_window, "scroll-forward-set-window", (FUNCTION_KEYSEQ *)0, "Scroll forward in this window and set default window size" },
   { (VFunction *)info_scroll_backward_set_window, "scroll-backward-set-window", (FUNCTION_KEYSEQ *)0, "Scroll backward in this window and set default window size" },
   { (VFunction *)info_scroll_forward_page_only, "scroll-forward-page-only", (FUNCTION_KEYSEQ *)0, "Scroll forward in this window staying within node" },
   { (VFunction *)info_scroll_backward_page_only, "scroll-backward-page-only", (FUNCTION_KEYSEQ *)0, "Scroll backward in this window staying within node" },
   { (VFunction *)info_scroll_forward_page_only_set_window, "scroll-forward-page-only-set-window", (FUNCTION_KEYSEQ *)0, "Scroll forward in this window staying within node and set default window size" },
   { (VFunction *)info_scroll_backward_page_only_set_window, "scroll-backward-page-only-set-window", (FUNCTION_KEYSEQ *)0, "Scroll backward in this window staying within node and set default window size" },
   { (VFunction *)info_down_line, "down-line", (FUNCTION_KEYSEQ *)0, "Scroll down by lines" },
   { (VFunction *)info_up_line, "up-line", (FUNCTION_KEYSEQ *)0, "Scroll up by lines" },
   { (VFunction *)info_scroll_half_screen_down, "scroll-half-screen-down", (FUNCTION_KEYSEQ *)0, "Scroll down by half screen size" },
   { (VFunction *)info_scroll_half_screen_up, "scroll-half-screen-up", (FUNCTION_KEYSEQ *)0, "Scroll up by half screen size" },
   { (VFunction *)info_scroll_other_window, "scroll-other-window", (FUNCTION_KEYSEQ *)0, "Scroll the other window" },
   { (VFunction *)info_scroll_other_window_backward, "scroll-other-window-backward", (FUNCTION_KEYSEQ *)0, "Scroll the other window backward" },
   { (VFunction *)info_next_window, "next-window", (FUNCTION_KEYSEQ *)0, "Select the next window" },
   { (VFunction *)info_prev_window, "prev-window", (FUNCTION_KEYSEQ *)0, "Select the previous window" },
   { (VFunction *)info_split_window, "split-window", (FUNCTION_KEYSEQ *)0, "Split the current window" },
   { (VFunction *)info_delete_window, "delete-window", (FUNCTION_KEYSEQ *)0, "Delete the current window" },
   { (VFunction *)info_keep_one_window, "keep-one-window", (FUNCTION_KEYSEQ *)0, "Delete all other windows" },
   { (VFunction *)info_grow_window, "grow-window", (FUNCTION_KEYSEQ *)0, "Grow (or shrink) this window" },
   { (VFunction *)info_tile_windows, "tile-windows", (FUNCTION_KEYSEQ *)0, "Divide the available screen space among the visible windows" },
   { (VFunction *)info_toggle_wrap, "toggle-wrap", (FUNCTION_KEYSEQ *)0, "Toggle the state of line wrapping in the current window" },
   { (VFunction *)info_menu_digit, "menu-digit", (FUNCTION_KEYSEQ *)0, "Select this menu item" },
   { (VFunction *)info_last_menu_item, "last-menu-item", (FUNCTION_KEYSEQ *)0, "Select the last item in this node's menu" },
   { (VFunction *)info_menu_item, "menu-item", (FUNCTION_KEYSEQ *)0, "Read a menu item and select its node" },
   { (VFunction *)info_xref_item, "xref-item", (FUNCTION_KEYSEQ *)0, "Read a footnote or cross reference and select its node" },
   { (VFunction *)info_find_menu, "find-menu", (FUNCTION_KEYSEQ *)0, "Move to the start of this node's menu" },
   { (VFunction *)info_visit_menu, "visit-menu", (FUNCTION_KEYSEQ *)0, "Visit as many menu items at once as possible" },
   { (VFunction *)info_move_to_prev_xref, "move-to-prev-xref", (FUNCTION_KEYSEQ *)0, "Move to the previous cross reference" },
   { (VFunction *)info_move_to_next_xref, "move-to-next-xref", (FUNCTION_KEYSEQ *)0, "Move to the next cross reference" },
   { (VFunction *)info_select_reference_this_line, "select-reference-this-line", (FUNCTION_KEYSEQ *)0, "Select reference or menu item appearing on this line" },
   { (VFunction *)info_menu_sequence, "menu-sequence", (FUNCTION_KEYSEQ *)0, "Read a list of menus starting from dir and follow them" },
   { (VFunction *)info_next_node, "next-node", (FUNCTION_KEYSEQ *)0, "Select the Next node" },
   { (VFunction *)info_prev_node, "prev-node", (FUNCTION_KEYSEQ *)0, "Select the Prev node" },
   { (VFunction *)info_up_node, "up-node", (FUNCTION_KEYSEQ *)0, "Select the Up node" },
   { (VFunction *)info_last_node, "last-node", (FUNCTION_KEYSEQ *)0, "Select the last node in this file" },
   { (VFunction *)info_first_node, "first-node", (FUNCTION_KEYSEQ *)0, "Select the first node in this file" },
   { (VFunction *)info_global_next_node, "global-next-node", (FUNCTION_KEYSEQ *)0, "Move forwards or down through node structure" },
   { (VFunction *)info_global_prev_node, "global-prev-node", (FUNCTION_KEYSEQ *)0, "Move backwards or up through node structure" },
   { (VFunction *)info_goto_node, "goto-node", (FUNCTION_KEYSEQ *)0, "Read a node name and select it" },
   { (VFunction *)info_goto_invocation_node, "goto-invocation-node", (FUNCTION_KEYSEQ *)0, "Find the node describing program invocation" },
   { (VFunction *)info_man, "man", (FUNCTION_KEYSEQ *)0, "Read a manpage reference and select it" },
   { (VFunction *)info_top_node, "top-node", (FUNCTION_KEYSEQ *)0, "Select the node 'Top' in this file" },
   { (VFunction *)info_dir_node, "dir-node", (FUNCTION_KEYSEQ *)0, "Select the node '(dir)'" },
   { (VFunction *)info_display_file_info, "display-file-info", (FUNCTION_KEYSEQ *)0, "Show full file name of node being displayed" },
   { (VFunction *)info_history_node, "history-node", (FUNCTION_KEYSEQ *)0, "Select the most recently selected node" },
   { (VFunction *)info_view_file, "view-file", (FUNCTION_KEYSEQ *)0, "Read the name of a file and select it" },
   { (VFunction *)info_print_node, "print-node", (FUNCTION_KEYSEQ *)0, "Pipe the contents of this node through INFO_PRINT_COMMAND" },
   { (VFunction *)info_toggle_regexp, "toggle-regexp", (FUNCTION_KEYSEQ *)0, "Toggle the usage of regular expressions in searches" },
   { (VFunction *)info_tree_search, "tree-search", (FUNCTION_KEYSEQ *)0, "Search this node and subnodes for a string" },
   { (VFunction *)info_tree_search_next, "tree-search-next", (FUNCTION_KEYSEQ *)0, "Go to next match in Info sub-tree" },
   { (VFunction *)info_tree_search_previous, "tree-search-previous", (FUNCTION_KEYSEQ *)0, "Go to previous match in Info sub-tree" },
   { (VFunction *)info_search_case_sensitively, "search-case-sensitively", (FUNCTION_KEYSEQ *)0, "Read a string and search for it case-sensitively" },
   { (VFunction *)info_search, "search", (FUNCTION_KEYSEQ *)0, "Read a string and search for it" },
   { (VFunction *)info_search_backward, "search-backward", (FUNCTION_KEYSEQ *)0, "Read a string and search backward for it" },
   { (VFunction *)info_search_next, "search-next", (FUNCTION_KEYSEQ *)0, "Repeat last search in the same direction" },
   { (VFunction *)info_search_previous, "search-previous", (FUNCTION_KEYSEQ *)0, "Repeat last search in the reverse direction" },
   { (VFunction *)info_clear_search, "clear-search", (FUNCTION_KEYSEQ *)0, "Clear displayed search matches" },
   { (VFunction *)isearch_forward, "isearch-forward", (FUNCTION_KEYSEQ *)0, "Search interactively for a string as you type it" },
   { (VFunction *)isearch_backward, "isearch-backward", (FUNCTION_KEYSEQ *)0, "Search interactively for a string as you type it" },
   { (VFunction *)info_abort_key, "abort-key", (FUNCTION_KEYSEQ *)0, "Cancel current operation" },
   { (VFunction *)info_info_version, "info-version", (FUNCTION_KEYSEQ *)0, "Display version of Info being run" },
   { (VFunction *)info_redraw_display, "redraw-display", (FUNCTION_KEYSEQ *)0, "Redraw the display" },
   { (VFunction *)info_quit, "quit", (FUNCTION_KEYSEQ *)0, "Quit using Info" },
   { (VFunction *)info_do_lowercase_version, "do-lowercase-version", (FUNCTION_KEYSEQ *)0, "Run command bound to this key's lowercase variant" },
   { (VFunction *)info_add_digit_to_numeric_arg, "add-digit-to-numeric-arg", (FUNCTION_KEYSEQ *)0, "Add this digit to the current numeric argument" },
   { (VFunction *)info_universal_argument, "universal-argument", (FUNCTION_KEYSEQ *)0, "Start (or multiply by 4) the current numeric argument" },
/* Commands found in "../../info/echo-area.c". */
   { (VFunction *)ea_forward, "echo-area-forward", (FUNCTION_KEYSEQ *)0, "Move forward a character" },
   { (VFunction *)ea_backward, "echo-area-backward", (FUNCTION_KEYSEQ *)0, "Move backward a character" },
   { (VFunction *)ea_beg_of_line, "echo-area-beg-of-line", (FUNCTION_KEYSEQ *)0, "Move to the start of this line" },
   { (VFunction *)ea_end_of_line, "echo-area-end-of-line", (FUNCTION_KEYSEQ *)0, "Move to the end of this line" },
   { (VFunction *)ea_forward_word, "echo-area-forward-word", (FUNCTION_KEYSEQ *)0, "Move forward a word" },
   { (VFunction *)ea_backward_word, "echo-area-backward-word", (FUNCTION_KEYSEQ *)0, "Move backward a word" },
   { (VFunction *)ea_delete, "echo-area-delete", (FUNCTION_KEYSEQ *)0, "Delete the character under the cursor" },
   { (VFunction *)ea_rubout, "echo-area-rubout", (FUNCTION_KEYSEQ *)0, "Delete the character behind the cursor" },
   { (VFunction *)ea_abort, "echo-area-abort", (FUNCTION_KEYSEQ *)0, "Cancel or quit operation" },
   { (VFunction *)ea_newline, "echo-area-newline", (FUNCTION_KEYSEQ *)0, "Accept (or force completion of) this line" },
   { (VFunction *)ea_quoted_insert, "echo-area-quoted-insert", (FUNCTION_KEYSEQ *)0, "Insert next character verbatim" },
   { (VFunction *)ea_tab_insert, "echo-area-tab-insert", (FUNCTION_KEYSEQ *)0, "Insert a TAB character" },
   { (VFunction *)ea_transpose_chars, "echo-area-transpose-chars", (FUNCTION_KEYSEQ *)0, "Transpose characters at point" },
   { (VFunction *)ea_yank, "echo-area-yank", (FUNCTION_KEYSEQ *)0, "Yank back the contents of the last kill" },
   { (VFunction *)ea_yank_pop, "echo-area-yank-pop", (FUNCTION_KEYSEQ *)0, "Yank back a previous kill" },
   { (VFunction *)ea_kill_line, "echo-area-kill-line", (FUNCTION_KEYSEQ *)0, "Kill to the end of the line" },
   { (VFunction *)ea_backward_kill_line, "echo-area-backward-kill-line", (FUNCTION_KEYSEQ *)0, "Kill to the beginning of the line" },
   { (VFunction *)ea_kill_word, "echo-area-kill-word", (FUNCTION_KEYSEQ *)0, "Kill the word following the cursor" },
   { (VFunction *)ea_backward_kill_word, "echo-area-backward-kill-word", (FUNCTION_KEYSEQ *)0, "Kill the word preceding the cursor" },
   { (VFunction *)ea_possible_completions, "echo-area-possible-completions", (FUNCTION_KEYSEQ *)0, "List possible completions" },
   { (VFunction *)ea_complete, "echo-area-complete", (FUNCTION_KEYSEQ *)0, "Insert completion" },
   { (VFunction *)ea_scroll_completions_window, "echo-area-scroll-completions-window", (FUNCTION_KEYSEQ *)0, "Scroll the completions window" },
/* Commands found in "../../info/infodoc.c". */
   { (VFunction *)info_get_help_window, "get-help-window", (FUNCTION_KEYSEQ *)0, "Display help message" },
   { (VFunction *)info_get_info_help_node, "get-info-help-node", (FUNCTION_KEYSEQ *)0, "Visit Info node '(info)Help'" },
   { (VFunction *)describe_key, "describe-key", (FUNCTION_KEYSEQ *)0, "Print documentation for KEY" },
   { (VFunction *)info_where_is, "where-is", (FUNCTION_KEYSEQ *)0, "Show what to type to execute a given command" },
/* Commands found in "../../info/m-x.c". */
   { (VFunction *)describe_command, "describe-command", (FUNCTION_KEYSEQ *)0, "Read the name of an Info command and describe it" },
   { (VFunction *)info_execute_command, "execute-command", (FUNCTION_KEYSEQ *)0, "Read a command name in the echo area and execute it" },
   { (VFunction *)set_screen_height, "set-screen-height", (FUNCTION_KEYSEQ *)0, "Set the height of the displayed window" },
/* Commands found in "../../info/indices.c". */
   { (VFunction *)info_index_search, "index-search", (FUNCTION_KEYSEQ *)0, "Look up a string in the index for this file" },
   { (VFunction *)info_next_index_match, "next-index-match", (FUNCTION_KEYSEQ *)0, "Go to the next matching index item from the last '\\[index-search]' command" },
   { (VFunction *)info_index_apropos, "index-apropos", (FUNCTION_KEYSEQ *)0, "Grovel all known info file's indices for a string and build a menu" },
   { (VFunction *)info_virtual_index, "virtual-index", (FUNCTION_KEYSEQ *)0, "List all matches of a string in the index" },
/* Commands found in "../../info/nodemenu.c". */
   { (VFunction *)list_visited_nodes, "list-visited-nodes", (FUNCTION_KEYSEQ *)0, "Make a window containing a menu of all of the currently visited nodes" },
   { (VFunction *)select_visited_node, "select-visited-node", (FUNCTION_KEYSEQ *)0, "Select a node which has been previously visited in a visible window" },
/* Commands found in "../../info/footnotes.c". */
   { (VFunction *)info_show_footnotes, "show-footnotes", (FUNCTION_KEYSEQ *)0, "Show the footnotes associated with this node in another window" },
/* Commands found in "../../info/variables.c". */
   { (VFunction *)describe_variable, "describe-variable", (FUNCTION_KEYSEQ *)0, "Explain the use of a variable" },
   { (VFunction *)set_variable, "set-variable", (FUNCTION_KEYSEQ *)0, "Set the value of an Info variable" },
   { NULL, NULL, NULL, NULL }
};
