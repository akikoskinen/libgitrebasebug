#ifndef TESTDIR
#error TESTDIR must be defined
#endif

// Specify whether to use libgit2 master branch (1) or 0.22 (0) API
#define LIBGIT_MASTER 1

#include <git2.h>
#include <assert.h>

int main(void) {
	git_libgit2_init();

	git_repository *repo;
	git_repository_open(&repo, TESTDIR);

	git_signature *signature;
	git_signature_now(&signature, "Test", "test@test.example");

	git_reference *masterRef, *otherRef;
	git_reference_lookup(&masterRef, repo, "refs/heads/master");
	git_reference_lookup(&otherRef, repo, "refs/heads/other");

	git_annotated_commit *master, *base, *other;
	git_annotated_commit_from_ref(&master, repo, masterRef);
	git_annotated_commit_from_ref(&other, repo, otherRef);

	git_commit *masterCommit, *baseCommit;
	git_commit_lookup(&masterCommit, repo, git_annotated_commit_id(master));
	git_commit_parent(&baseCommit, masterCommit, 0);
	git_annotated_commit_lookup(&base, repo, git_commit_id(baseCommit));

	git_rebase *rebase;
	git_rebase_operation *operation;

#if LIBGIT_MASTER
	git_rebase_init(&rebase, repo, master, base, other, NULL);
	assert(git_rebase_next(&operation, rebase) == GIT_OK);
#else
	git_rebase_init(&rebase, repo, master, base, other, NULL, NULL);
	assert(git_rebase_next(&operation, rebase, NULL) == GIT_OK);
#endif

	return 0;
}
