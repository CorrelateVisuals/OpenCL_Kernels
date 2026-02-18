# Contributing to OpenCL Kernels

Thank you for your interest in contributing to the OpenCL Kernels project! This document provides guidelines and information for contributors.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How to Contribute](#how-to-contribute)
- [Reporting Bugs](#reporting-bugs)
- [Suggesting Enhancements](#suggesting-enhancements)
- [Pull Request Process](#pull-request-process)
- [Coding Standards](#coding-standards)
- [Project Structure](#project-structure)
- [Testing](#testing)

## Code of Conduct

This project follows a simple code of conduct:
- Be respectful and constructive in all interactions
- Focus on what is best for the community and the project
- Show empathy towards other community members
- Accept constructive criticism gracefully

## How to Contribute

There are many ways to contribute to this project:

1. **Report bugs** - Help us identify and fix issues
2. **Suggest enhancements** - Propose new features or improvements
3. **Submit pull requests** - Contribute code, documentation, or examples
4. **Improve documentation** - Help make the project more accessible
5. **Share your use cases** - Tell us how you're using the project

## Reporting Bugs

When reporting bugs, please include:

### Bug Report Template

```markdown
**Description**
A clear description of the bug

**To Reproduce**
Steps to reproduce the behavior:
1. Compile with '...'
2. Run with '...'
3. See error

**Expected Behavior**
What you expected to happen

**Actual Behavior**
What actually happened

**Environment**
- OS: [e.g., Windows 10, Ubuntu 20.04]
- OpenCL Version: [e.g., 2.0]
- GPU/Device: [e.g., NVIDIA GTX 1080]
- Compiler: [e.g., MSVC 2019, GCC 9.3]

**Additional Context**
Any other relevant information
```

## Suggesting Enhancements

We welcome suggestions for new features or improvements! When suggesting enhancements:

1. **Check existing issues** - Someone may have already suggested it
2. **Be specific** - Clearly describe the enhancement and its benefits
3. **Provide examples** - If possible, show how it would work
4. **Consider scope** - Keep suggestions focused and achievable

### Enhancement Template

```markdown
**Feature Description**
A clear description of the proposed feature

**Use Case**
Why this feature would be valuable

**Proposed Implementation**
How you envision this working (optional)

**Alternatives Considered**
Other approaches you've thought about (optional)
```

## Pull Request Process

### Before Submitting a PR

1. **Fork the repository** and create a branch from `main`
2. **Follow coding standards** (see below)
3. **Test your changes** thoroughly
4. **Update documentation** if needed
5. **Keep changes focused** - One feature/fix per PR

### PR Guidelines

1. **Clear title and description**
   - Summarize what the PR does
   - Reference any related issues (e.g., "Fixes #123")

2. **Small, focused changes**
   - Easier to review and merge
   - Less likely to introduce bugs

3. **Documentation**
   - Update README files for new features
   - Add code comments for complex logic
   - Include usage examples where appropriate

4. **Commit messages**
   - Use clear, descriptive commit messages
   - Format: "Add feature X" or "Fix bug in Y"
   - Avoid generic messages like "Update" or "Fix"

### PR Review Process

1. Maintainers will review your PR
2. Address any feedback or requested changes
3. Once approved, a maintainer will merge your PR

## Coding Standards

### C++ Style Guidelines

**General Principles:**
- Write clear, readable code
- Follow existing code style in the project
- Prefer simplicity over cleverness
- Comment non-obvious code

**Formatting:**
```cpp
// Use 2-space indentation
void functionName() {
  if (condition) {
    // Code here
  }
}

// Use descriptive variable names
int imageWidth;      // Good
int w;               // Avoid

// Constants in camelCase or UPPER_CASE
const int maxIterations = 100;
const int MAX_BUFFER_SIZE = 1024;
```

**OpenCL Kernel Style:**
```cpp
// Kernel names should be descriptive
__kernel void boxBlur(...) { }
__kernel void edgeDetection(...) { }

// Use clear variable names even in kernels
int x = get_global_id(0);  // Good
int i = get_global_id(0);  // Less clear
```

### File Organization

**Project Structure:**
```
ProjectName/
├── README.md              # Project-specific documentation
├── main.cpp               # Main program file
├── *.sln                  # Visual Studio solution
├── *.vcxproj              # Visual Studio project file
└── [additional sources]   # Other source files as needed
```

**Source File Guidelines:**
- One main program per directory
- Include necessary headers at the top
- Group related functions together
- Keep OpenCL kernel code readable and well-commented

### Documentation Standards

**README Files:**
- Include clear description of what the project does
- Provide building instructions for multiple platforms
- Show usage examples with actual commands
- Document any configurable parameters

**Code Comments:**
```cpp
// Use comments to explain WHY, not WHAT
// Good: "Clamp to prevent overflow in next calculation"
// Poor: "Set x to 255"

// Document complex algorithms
/**
 * Performs parallel BFS traversal using level synchronization.
 * Each work item processes one node from the current frontier.
 */
__kernel void bfs(...) { }
```

## Project Structure

When adding new projects:

1. **Create a new directory** with a descriptive name (e.g., `OpenCL_Feature_Name`)
2. **Include these files:**
   - `README.md` - Project-specific documentation
   - `main.cpp` - Main source file
   - `.sln` and `.vcxproj` - Visual Studio files (if applicable)
   - Any additional source files

3. **Update main README.md** - Add your project to the projects list
4. **Follow naming conventions** - Use `OpenCL_` prefix for consistency

## Testing

### Manual Testing

Before submitting:

1. **Build on your platform** - Ensure code compiles without warnings
2. **Test functionality** - Verify the program works as expected
3. **Test edge cases** - Try different inputs, including edge cases
4. **Check memory** - Ensure no memory leaks or access violations

### Platforms to Consider

If possible, test on:
- Windows with MSVC
- Linux with GCC
- Different OpenCL devices (GPU, CPU)
- Various image sizes/inputs

### What to Report

Include in your PR description:
- Platforms tested
- OpenCL devices tested
- Test results and any issues found

## Adding New Examples

When contributing new OpenCL examples:

1. **Choose meaningful examples** - Focus on educational value
2. **Include sample data** - Provide test inputs if applicable
3. **Document performance** - Share benchmark results if relevant
4. **Explain the algorithm** - Help others understand the implementation
5. **Show real-world applications** - Explain when this would be useful

### Example Checklist

- [ ] Clear, descriptive project name
- [ ] Comprehensive README with usage instructions
- [ ] Compiles without warnings on at least one platform
- [ ] Includes example output or sample data
- [ ] OpenCL kernel is well-commented
- [ ] Follows project coding standards

## Questions?

If you have questions about contributing:

1. Check existing issues and discussions
2. Open a new issue with your question
3. Tag it appropriately (e.g., "question", "help wanted")

## License

By contributing to this project, you agree that your contributions will be licensed under the CC0 1.0 Universal License (public domain).

---

Thank you for contributing to OpenCL Kernels! Your efforts help make GPU computing more accessible to everyone.
