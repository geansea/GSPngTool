#include <QCoreApplication>
#include "PngCmdArgs.h"
#include "PngCmdUtils.h"

static const QString CMD_HELP = "-h";
static const QString CMD_INFO = "-i";
static const QString CMD_OPT1 = "-o1";

bool ShowHelp()
{
    printf("Usage: GSPngCmd <command> [input path] [output path]\n");
    printf("    -h  show help\n");
    printf("    -i  show input file info\n");
    printf("    -o1 \n");
    return true;
}

int main(int argc, char *argv[])
{
    PngCmdArgs args(argc, argv);
    QString cmd = args.GetCommand();
    bool ret = false;
    if (cmd == CMD_HELP)
    {
        ret = ShowHelp();
    }
    else if (cmd == CMD_INFO)
    {
        ret = PngCmdUtils::ShowInfo(args.GetInputPath());
    }
    else if (cmd == CMD_OPT1)
    {
        ret = PngCmdUtils::OpiFile(args.GetInputPath(), args.GetOutputPath());
    }
    else
    {
        printf("Unsupported command\n");
        ShowHelp();
    }
    return ret ? 0 : 1;
}
