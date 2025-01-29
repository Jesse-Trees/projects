import sys
import os
import json
from gradescope_utils.autograder_utils.json_test_runner import JSONTestRunner
from TestingFramework import TestRegister


def gradescopePostProcessing(_results: dict, _submissionLimit: int, _takeHighest: bool):
    if not os.path.exists("/autograder/submission_metadata.json"):
        return

    # Enforce submission limit
    submissionMetadata: dict = {}
    with open("/autograder/submission_metadata.json", 'r') as submissionMetadataIn:
        submissionMetadata = json.load(submissionMetadataIn)

    previousSubmissions: list[dict] = submissionMetadata['previous_submissions']

    _results['output'] = f"Submission {len(previousSubmissions) + 1} of {_submissionLimit}.\n"

    validSubmissions: list[dict] = \
        [previousSubmissionMetadata['results']
         for previousSubmissionMetadata in previousSubmissions
         if 'results' in previousSubmissionMetadata.keys()
         ]

    validSubmissions.append(_results)

    # submission limit exceeded
    if len(validSubmissions) > _submissionLimit:
        _results['output'] += f"Submission limit exceeded.\n" \
                              f"Autograder has been run on your code so you can see how you did\n" \
                              f"but, your score will be highest of your valid submissions.\n"
        validSubmissions = validSubmissions[:_submissionLimit]
        # We should take the highest valid submission
        _takeHighest = True

    # sorts in descending order
    validSubmissions.sort(reverse=True, key=lambda submission: submission['score'])

    if _takeHighest and validSubmissions[0] != _results:
        _results['output'] += f"Score has been set to your highest valid score.\n"
        _results['score'] = validSubmissions[0]['score']

    # ensure that negative scores arent possible
    if _results['score'] < 0:
        _results['output'] += f"Score has been set to a floor of 0 to ensure no negative scores.\n"
        _results['score'] = 0


def main(runUnitTestsOnly: bool, _resultsPath: str | None):
    testSuite = TestRegister()

    if runUnitTestsOnly:
        from BetterPyUnitFormat.BetterPyUnitTestRunner import BetterPyUnitTestRunner
        testRunner = BetterPyUnitTestRunner()
        testRunner.run(testSuite)
        return

    with open(_resultsPath, 'w+') as results:
        testRunner = JSONTestRunner(visibility='visible',
                                    stream=results,
                                    post_processor=lambda _resultsDict: gradescopePostProcessing(_resultsDict, 4, True))
        testRunner.run(testSuite)


if __name__ == "__main__":
    resultsPath: str = "/autograder/results/results.json"
    if len(sys.argv) == 2 and sys.argv[1] == "--local":
        resultsPath = "../student/results/results.json"

    main(len(sys.argv) == 3 and sys.argv[1] == "--unit-test-only", resultsPath)
