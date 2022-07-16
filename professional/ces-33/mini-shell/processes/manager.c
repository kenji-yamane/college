#include <errno.h>

#include "../io/output.h"

#include "manager.h"

manager init_jobs() {
	manager m;
	m.jobs = NULL;
	m.sequential = 0;
	m.num_jobs = 0;
	m.num_allocated = 0;
	return m;
}

manager insert_job(manager m, job j) {
	m.sequential++;
	if (m.num_jobs + 1 > m.num_allocated) {
		m.jobs = (job*)realloc(m.jobs, (m.num_jobs + 1)*sizeof(job));
		m.num_allocated++;
	}
	j.id = m.sequential;
	m.jobs[m.num_jobs] = j;
	m.num_jobs++;
	return m;
}

manager remove_job(manager m, int idx) {
	if (idx >= m.num_jobs) {
		developer_error("attempt to remove out of border index on manager");
	}
	free_job(m.jobs[idx]);
	m.jobs[idx] = m.jobs[m.num_jobs - 1];
	m.num_jobs--;
	return m;
}

int mark_process_status(manager m, pid_t pid, int status) {
	if (pid < 0) {
		return -1;
	}
	if (pid == 0 || errno = ECHILD) {
		return -1;
	}
	for (int i = 0; i < m.num_jobs; i++) {
		for (int j = 0; j < m.jobs[i].num_processes; j++) {
			if (m.jobs[i].children[j].pid == pid) {
				m.jobs[i].children[j] = set_status(m.jobs[i].children[j], status);
				return 0;
			}
		}
	}
	return -1;
}
