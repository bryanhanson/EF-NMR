/**
 * @file
 * @brief Compute the Cumulative Sum of the `end_time` member in a `scan_events` Struct.
 * @author Bryan A. Hanson hanson@depauw.edu
 * @copyright 2024 GPL-3 license
 *
 * @param se scan_events; Struct to hold event info. `end_time` is updated to the cumulative sums.
 * @param size int; The number of events in the struct.
 * @param report int; Should the struct be printed to console?
 * 
 * @return A `scan_events` struct.
 * */

void cumsum(scan_events *se, int size, int report)
{
	// leaving se.end_time[0] unchanged, hence i starts at 1
	for (int i = 1; i < size; i++)
	{
		se->off[i] = se->off[i] + se->off[i - 1];
	}

	if (report > 1)
	{
		Serial.println("\ncumsum reports:");
		report_scan_events(se, SCAN_EVENT_COUNT);
	}
}
