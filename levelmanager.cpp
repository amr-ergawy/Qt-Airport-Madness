#include "levelmanager.h"

LevelManager *LevelManager::m_instance = 0;
QGraphicsView *LevelManager::gameView = 0;
GameLevel *LevelManager::currentLevel = 0;

bool LevelManager::createLevel(int levelIndex)
{
    // Create level file and image file names
    QString fileName = QString(":/levels/level-");
    QString imageFileName = QString(":/arts/level-");
    switch (levelIndex) {
    case 1:
        fileName.append("1.lvl");
        imageFileName.append("1.png");
        break;
    default:
        //TODO: Log error message
        return false;
    };

    std::cout << "Assumed level file: "
              << fileName.toStdString()
              << std::endl;
    std::cout << "Assumed image level file: "
              << imageFileName.toStdString()
              << std::endl;
    
    // Open level file
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "Error opening assumed level file: "
                  << file.errorString().toStdString()
                  << std::endl;
        return false;
    }

    // Parse level file
    parseLevelFile(&file);

    //load the level image to the game view
    gameView->setBackgroundBrush(QPixmap(imageFileName));

    return true;
}

bool LevelManager::parseLevelFile(QIODevice *device)
{
    QDomDocument levelDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;

    if (!levelDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn)) {
        std::cout << "Error loading assumed level file: "
                  << errorStr.toStdString()
                  << std::endl;
        return false;
    }

    QDomElement root = levelDocument.documentElement();
    if (root.tagName() != "level") {
        std::cout << "This is not a level file"
                  << std::endl;
        return false;
    }

    if (root.attribute("new-plane-interval").isNull() ||
        root.attribute("new-plane-interval").isEmpty()) {
        std::cout << "Invalid new-plane-interval"
                  << std::endl;
        return false;
    }

    long newPlaneInterval = root.attribute("new-plane-interval").toLong();
    std::cout << "New plane interval "
              << newPlaneInterval
              << std::endl;

    int maxNumberOfPlanes = root.attribute("max-number-of-planes").toInt();
    std::cout << "Max number of planes "
              <<  maxNumberOfPlanes
              << std::endl;

    this->currentLevel = new GameLevel(newPlaneInterval, maxNumberOfPlanes);

    QDomElement child = root.firstChildElement("runway");
    RunWay * runWay;
    while (!child.isNull()) {
        runWay = initializeRunway(child);
        if (runWay == NULL) {
            // TODO : log failure message
            return false;
        }
        this->currentLevel->addRunWay(runWay);
        child = child.nextSiblingElement("runway");
    }

    return true;
}

RunWay * LevelManager::initializeRunway(const QDomElement &runWayElement) {

    RunWay * runWay = new RunWay();

    QDomElement directionElement = runWayElement.firstChildElement("direction");
    while (!directionElement.isNull()) {

        // Print name
        QString directionName = directionElement.attribute("name");
        if (directionName.isNull() ||
            directionName.isEmpty()) {
            std::cout << "Invalid direction name"
                      << std::endl;
            return NULL;
        }

        std::cout << "Direction "
                  << directionName.toStdString()
                  << std::endl;

        // Create the direction
        PlaneDirection * planeDirection = new PlaneDirection();
        if (directionName.operator ==("departure")) {
            runWay->setDeparturePath(planeDirection);
        } else if (directionName.operator ==("arrival")) {
            runWay->setArrivalPath(planeDirection);
        } else {
            std::cout << "Invalid direction type"
                      << std::endl;
            return NULL;
        }

        // Add maneuvers to direction
        QDomElement maneuverElement = directionElement.firstChildElement("maneuver");
        while(!maneuverElement.isNull()) {
            if (maneuverElement.attribute("name").isNull() ||
                maneuverElement.attribute("name").isEmpty()) {
                std::cout << "Invalid maneuver"
                          << std::endl;
                return NULL;
            }

            QString * maneuverName = new QString(maneuverElement.attribute("name"));

            std::cout << "Maneuver " << maneuverName->toStdString()
                      << std::endl;

            ManeuverDescription * maneuverDescription = new ManeuverDescription(maneuverName);
            planeDirection->addManeuverDescription(maneuverDescription);

            // Add segments to maneuver
            QDomElement segmentElement = maneuverElement.firstChildElement("segment");
            while(!segmentElement.isNull()) {
                if (segmentElement.attribute("type").isNull() ||
                    segmentElement.attribute("type").isEmpty() ||
                    segmentElement.attribute("index").isNull() ||
                    segmentElement.attribute("index").isEmpty()) {
                    std::cout << "Empty segment type or index"
                              << std::endl;
                    return NULL;
                }

                QString * segmentType = new QString(segmentElement.attribute("type"));
                int segmentIndex = segmentElement.attribute("index").toInt();
                std::cout << "Segment: " << segmentType->toStdString()
                          << ", " << segmentIndex
                          << std::endl;

                // Creating the segment
                ManeuverSegment * maneuverSegment = NULL;
                if (segmentType->operator ==("line")) {
                    std::cout << "Creating line segment ..."
                              << std::endl;
                    maneuverSegment = (ManeuverSegment *) LineManeuverSegment::getInstance(segmentElement);
                } else if (segmentType->operator ==("angle")) {
                    std::cout << "Creating angle segment ..."
                              << std::endl;
                    maneuverSegment = (ManeuverSegment *) AngleManeuverSegment::getInstance(segmentElement);
                } else if (segmentType->operator ==("bezier")) {
                    std::cout << "Creating bezier segment ..."
                              << std::endl;
                    maneuverSegment = (ManeuverSegment *) BezierManeuverSegment::getInstance(segmentElement);
                }

                if (maneuverSegment == NULL) {
                    std::cout << "Invalid segment type"
                              << std::endl;
                    return NULL;
                }

                // Building references
                if (!planeDirection->addManeuverSegment(segmentIndex, maneuverSegment)) {
                   return NULL;
                }
                maneuverDescription->addManeuverSegmentIndex(segmentIndex);

                segmentElement = segmentElement.nextSiblingElement("segment");
            }

            maneuverElement = maneuverElement.nextSiblingElement("maneuver");
        }

        // Resolve segments cross referencing
        if (!planeDirection->resolveSegmentsCrossReferences()) {
            return NULL;
        }
        directionElement = directionElement.nextSiblingElement("direction");
    }
    return runWay;
}

GameLevel * LevelManager::getCurrentLevel()
{
    return this->currentLevel;
}

QGraphicsScene * LevelManager::getLevelScene()
{
    return this->gameView->scene();
}
