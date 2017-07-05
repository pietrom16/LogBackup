# LogBackup

(C) Pietro Mele 2017

Utility to move a file appending it to another file.

Used to move logs from one disk to another, typically from a RAM-disk
to a hard disk.

Once launched, it runs in the background.

* Syntax:

	`logbkp --source SRC --dest DEST --interval TIME_INT --maxsize MAX_SIZE`
	`       --config CONFIG_FILE`

	`logbkp -s SRC -d DEST -i TIME_INT -m MAX_SIZE -c CONFIG_FILE`

| Arguments     |                                                            | Default
| --------------|------------------------------------------------------------|---------
| `SRC`         | path of the source file on a temporary device.             |
| `DEST`        | path of the destination file on a permanent device.        |
| `TIME_INT`    | time interval between checks (in seconds).                 |  1 sec
| `MAX_SIZE`    | source file size that triggers the move (in KB).           |  8 KB
| `CONFIG_FILE` | configuration file (JSON format) with parameters that can change during the run. |

