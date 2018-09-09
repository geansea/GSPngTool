#include <QCoreApplication>
#include "PngCmdArgs.h"
#include "PngCmdUtils.h"

static const QString CMD_HELP = "-h";
static const QString CMD_INFO = "-i";

bool ShowHelp()
{
    printf("Usage: GSPngCmd <command> [input path] [output path]\n");
    printf("    -h  show help\n");
    printf("    -i  show input file info\n");
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
    else
    {
        printf("Unsupported command\n");
        ShowHelp();
    }
    return ret ? 0 : 1;
}
