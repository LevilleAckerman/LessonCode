CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TARGET = $(BINDIR)/WPSMeetingSystem

# 查找所有cpp文件
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

# 默认目标
all: $(TARGET)

# 链接目标文件生成可执行文件
$(TARGET): $(OBJECTS) | $(BINDIR)
	$(CXX) $(OBJECTS) -o $(TARGET)

# 编译源文件生成目标文件
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 创建必要的目录
$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# 清理构建文件
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 显示帮助信息
help:
	@echo "可用命令:"
	@echo "  make all    - 编译整个项目"
	@echo "  make clean  - 清理构建文件"
	@echo "  make run    - 编译并运行程序"
	@echo "  make help   - 显示此帮助信息"

.PHONY: all clean run help