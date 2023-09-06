package program_test

import (
	"testing"
	"os/exec"
	"time"
)

const timeout = 5

func compile(programName string) error {
	_, err := exec.Command("./comp", programName, "void").Output()
	return err
}

func generateBinary() error {
	_, err := exec.Command("gcc", "./generated/out.s").Output()
	return err
}

func run() ([]byte, error) {
	return exec.Command("./a.out").Output()
}

func cleanup() error {
	_, err := exec.Command("rm", "a.out").Output()
	if err != nil{
		return err
	}

	_, err = exec.Command("rm", "generated/out.s").Output()

	return err
}

func TestPrograms(t *testing.T) {
	defer cleanup()

	tests := []struct{
		programName string
		expectedOutput string
	}{
		{ "program1.comp", "Hello, world!"},
		{ "program2.comp", "10"},
		{ "program3.comp", "a b c 96 97 98"},
		{ "program4.comp", "1000"},
		{ "program5.comp", "542.250000"},
		{ "program6.comp", "6\n9\n5\n2\n7\n8\n1\n10\n3\n4\n--\n\n10\n9\n8\n7\n6\n5\n4\n3\n2\n1\n"},
	}

	for _, test := range tests {
		go func() {
			time.Sleep(time.Duration(timeout) * time.Second)
			t.Errorf("%s did not finished in time\n", test.programName)
		}()
		
		err := compile(test.programName)
		if err != nil {
			t.Errorf("failed to compile %s (%s)\n", test.programName, err.Error())
		}

		err = generateBinary()
		if err != nil {
			t.Errorf("failed to generate %s binary (%s)\n", test.programName, err.Error())
		}

		output, err := run()
		if err != nil {
			t.Errorf("failed to run %s (%s)", test.programName, err.Error())
		}

		if string(output) != test.expectedOutput {
			t.Errorf("invalid output, expected [%s] got [%s] on %s\n", test.expectedOutput, string(output), test.programName)
		}

		t.Logf("\n\n%s%s%s%s", test.programName, ":\n", string(output), "\n\n")
	}
}