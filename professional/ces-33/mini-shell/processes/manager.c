#include <errno.h>
#include <stdlib.h>

#include <sys/wait.h>
#include <sys/types.h>

#include "../io/output.h"

#include "manager.h"

manager init_manager() {
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

int get_job_idx_from_id(manager m, int id) {
	if (m.num_jobs == 0) {
		return -1;
	}
	int ini = 0, fin = m.num_jobs;

	while (ini <= fin) {
		int middle = (ini + fin)/2;
		if (id < m.jobs[middle].id) {
			fin = middle - 1;
		} else if (m.jobs[middle].id < id) {
			ini = middle + 1;
		} else {
			return middle;
		}
	}

	return -1;
}

manager remove_job(manager m, int idx) {
	if (idx >= m.num_jobs) {
		developer_error("attempt to remove out of border index on manager");
	}
	free_job(m.jobs[idx]);
	m.num_jobs--;
	for (int i = idx; i < m.num_jobs; i++) {
        m.jobs[i] = m.jobs[i + 1];
    }
	return m;
}

manager notify_job_events(manager m) {
	update_all_processes(m);

	int *ids_to_remove = (int*)malloc(m.num_jobs*sizeof(int)), num_to_remove = 0;
	for (int i = 0; i < m.num_jobs; i++) {
		bool completed = job_completed(m.jobs[i]), stopped = job_stopped(m.jobs[i]);
		if (completed) {
			notify_completed_job(m.jobs[i]);
			ids_to_remove[num_to_remove++] = m.jobs[i].id;
		} else if (stopped) {
			m.jobs[i] = notify_stopped_job(m.jobs[i]);
		}
	}
	for (int i = 0; i < num_to_remove; i++) {
		int idx = get_job_idx_from_id(m, ids_to_remove[i]);
		m = remove_job(m, idx);
	}
	free(ids_to_remove);

	return m;
}

manager jobs_debrief(manager m) {
	update_all_processes(m);

	int *ids_to_remove = (int*)malloc(m.num_jobs*sizeof(int)), num_to_remove = 0;
	for (int i = 0; i < m.num_jobs; i++) {
		bool completed = job_completed(m.jobs[i]), stopped = job_stopped(m.jobs[i]);
		if (completed) {
			print_job_info(m.jobs[i], "completed");
			ids_to_remove[num_to_remove++] = m.jobs[i].id;
		} else if (stopped) {
			print_job_info(m.jobs[i], "stopped");
		} else {
			print_job_info(m.jobs[i], "running");
		}
	}
	for (int i = 0; i < num_to_remove; i++) {
		int idx = get_job_idx_from_id(m, ids_to_remove[i]);
		if (idx == -1) {
			developer_error("job with given id does not exist currently");
		}
		m = remove_job(m, idx);
	}
	free(ids_to_remove);

	return m;
}

void update_all_processes(manager m) {
	int status;
	pid_t pid;

	do {
		pid = waitpid(-1, &status, WUNTRACED|WNOHANG);
	} while (!mark_process_status(m, pid, status));
}

int mark_process_status(manager m, pid_t pid, int status) {
	if (pid < 0) {
		return -1;
	}
	if (pid == 0 || errno == ECHILD) {
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

void free_manager(manager m) {
	for (int i = 0; i < m.num_jobs; i++) {
		free_job(m.jobs[i]);
	}
	if (m.num_jobs > 0) {
		free(m.jobs);
	}
}

